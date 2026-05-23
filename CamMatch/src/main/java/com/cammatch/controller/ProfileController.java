package com.cammatch.controller;

import com.cammatch.entity.Camera;
import com.cammatch.entity.UserAccount;
import com.cammatch.entity.UserCamera;
import com.cammatch.repository.CameraRepository;
import com.cammatch.repository.FavoriteRepository;
import com.cammatch.repository.SearchHistoryRepository;
import com.cammatch.repository.UserCameraRepository;
import com.cammatch.repository.UserRepository;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

import java.math.BigDecimal;
import java.security.Principal;

@Controller
public class ProfileController {
    private final UserRepository userRepository;
    private final UserCameraRepository userCameraRepository;
    private final CameraRepository cameraRepository;
    private final FavoriteRepository favoriteRepository;
    private final SearchHistoryRepository searchHistoryRepository;

    public ProfileController(UserRepository userRepository, UserCameraRepository userCameraRepository, CameraRepository cameraRepository, FavoriteRepository favoriteRepository, SearchHistoryRepository searchHistoryRepository) {
        this.userRepository = userRepository;
        this.userCameraRepository = userCameraRepository;
        this.cameraRepository = cameraRepository;
        this.favoriteRepository = favoriteRepository;
        this.searchHistoryRepository = searchHistoryRepository;
    }

    @GetMapping("/profile")
    public String profile(Principal principal, Model model) {
        UserAccount user = currentUser(principal);
        UserCamera savedCamera = userCameraRepository.findByOwner(user).orElse(null);
        model.addAttribute("user", user);
        model.addAttribute("userCamera", savedCamera == null ? new UserCamera() : savedCamera);
        model.addAttribute("savedUserCamera", savedCamera);
        model.addAttribute("favorites", favoriteRepository.findByUserOrderByCreatedAtDesc(user));
        model.addAttribute("searchHistory", searchHistoryRepository.findTop5ByUserOrderByCreatedAtDesc(user));
        return "profile";
    }

    @PostMapping("/profile")
    @Transactional
    public String updateProfile(Principal principal, @RequestParam String username, @RequestParam(required = false) String experienceLevel, @RequestParam(required = false) String city, @RequestParam(required = false) String bio) {
        UserAccount user = currentUser(principal);
        if (username == null || username.trim().length() < 3) {
            return "redirect:/profile?usernameError=true";
        }
        user.setUsername(username.trim());
        user.setExperienceLevel(experienceLevel);
        user.setCity(city);
        user.setBio(bio);
        userRepository.save(user);
        return "redirect:/profile?updated=true";
    }

    @PostMapping("/profile/camera")
    @Transactional
    public String saveUserCamera(
            Principal principal,
            @RequestParam String brand,
            @RequestParam String model,
            @RequestParam(required = false) String type,
            @RequestParam(required = false) String photographyType,
            @RequestParam(required = false) Double resolutionMp,
            @RequestParam(required = false) Integer batteryShots,
            @RequestParam(required = false) String sensor,
            @RequestParam(required = false) String video,
            @RequestParam(required = false) BigDecimal price,
            @RequestParam(required = false) String imageUrl,
            @RequestParam(required = false) String notes) {
        UserAccount user = currentUser(principal);
        UserCamera userCamera = userCameraRepository.findByOwner(user).orElse(new UserCamera());
        userCamera.setOwner(user);
        userCamera.setBrand(clean(brand));
        userCamera.setModel(clean(model));
        userCamera.setType(defaultText(type, "Camera personala"));
        userCamera.setPhotographyType(defaultText(photographyType, "personal"));
        userCamera.setResolutionMp(resolutionMp);
        userCamera.setBatteryShots(batteryShots);
        userCamera.setSensor(defaultText(sensor, "Nespecificat"));
        userCamera.setVideo(defaultText(video, "Nespecificat"));
        userCamera.setPrice(price);
        userCamera.setImageUrl(cleanOrNull(imageUrl));
        userCamera.setNotes(notes);

        Camera publicCamera = userCamera.getPublicCamera();
        if (publicCamera == null) {
            publicCamera = new Camera();
            publicCamera.setAverageRating(0.0);
            publicCamera.setRatingCount(0);
        }
        publicCamera.setBrand(userCamera.getBrand());
        publicCamera.setModel(userCamera.getModel());
        publicCamera.setType(userCamera.getType());
        publicCamera.setPhotographyType(userCamera.getPhotographyType());
        publicCamera.setSensor(userCamera.getSensor());
        publicCamera.setVideo(userCamera.getVideo());
        publicCamera.setPrice(price == null || price.compareTo(BigDecimal.ZERO) < 0 ? BigDecimal.ZERO : price);
        publicCamera.setResolutionMp(resolutionMp == null || resolutionMp < 1 ? 1.0 : resolutionMp);
        publicCamera.setBatteryShots(batteryShots == null || batteryShots < 1 ? 1 : batteryShots);
        publicCamera.setImageUrl(resolveImage(userCamera.getBrand(), imageUrl));
        publicCamera.setDescription("Camera adaugata de utilizatorul " + user.getUsername() + ". " + (notes == null ? "" : notes.trim()));
        Camera savedPublicCamera = cameraRepository.save(publicCamera);

        userCamera.setPublicCamera(savedPublicCamera);
        UserCamera savedCamera = userCameraRepository.save(userCamera);
        user.setUserCamera(savedCamera);
        userRepository.save(user);

        return "redirect:/profile?cameraSaved=true";
    }

    @PostMapping("/profile/camera/delete")
    @Transactional
    public String deleteUserCamera(Principal principal) {
        UserAccount user = currentUser(principal);
        UserCamera userCamera = userCameraRepository.findByOwner(user).orElse(null);
        if (userCamera == null) {
            return "redirect:/profile?cameraMissing=true";
        }

        Camera publicCamera = userCamera.getPublicCamera();
        user.setUserCamera(null);
        userRepository.save(user);

        userCamera.setPublicCamera(null);
        userCameraRepository.delete(userCamera);
        userCameraRepository.flush();

        if (publicCamera != null) {
            favoriteRepository.deleteByCamera(publicCamera);
            cameraRepository.delete(publicCamera);
        }

        return "redirect:/profile?cameraDeleted=true";
    }

    private UserAccount currentUser(Principal principal) {
        return userRepository.findByEmail(principal.getName()).orElseThrow();
    }

    private String clean(String value) {
        return value == null ? "" : value.trim();
    }

    private String cleanOrNull(String value) {
        if (value == null || value.trim().isBlank()) {
            return null;
        }
        return value.trim();
    }

    private String defaultText(String value, String fallback) {
        if (value == null || value.trim().isBlank()) {
            return fallback;
        }
        return value.trim();
    }

    private String resolveImage(String brand, String imageUrl) {
        String customImage = cleanOrNull(imageUrl);
        if (isValidImageReference(customImage)) {
            return customImage;
        }
        return imageForBrand(brand);
    }

    private boolean isValidImageReference(String imageUrl) {
        if (imageUrl == null) {
            return false;
        }
        String normalized = imageUrl.trim().toLowerCase();
        return normalized.startsWith("/images/")
                || normalized.startsWith("http://")
                || normalized.startsWith("https://")
                || normalized.startsWith("data:image/");
    }

    private String imageForBrand(String brand) {
        if (brand == null) {
            return "/images/camera-placeholder.svg";
        }
        String normalized = brand.trim().toLowerCase().replace(" ", "-");
        return switch (normalized) {
            case "canon" -> "/images/brands/canon.svg";
            case "nikon" -> "/images/brands/nikon.svg";
            case "sony" -> "/images/brands/sony.svg";
            case "fujifilm" -> "/images/brands/fujifilm.svg";
            case "panasonic" -> "/images/brands/panasonic.svg";
            case "olympus" -> "/images/brands/olympus.svg";
            case "om-system" -> "/images/brands/om-system.svg";
            case "leica" -> "/images/brands/leica.svg";
            case "pentax" -> "/images/brands/pentax.svg";
            case "hasselblad" -> "/images/brands/hasselblad.svg";
            case "gopro" -> "/images/brands/gopro.svg";
            case "dji" -> "/images/brands/dji.svg";
            case "ricoh" -> "/images/brands/ricoh.svg";
            default -> "/images/camera-placeholder.svg";
        };
    }
}
