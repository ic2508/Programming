package com.cammatch.controller;

import com.cammatch.entity.Camera;
import com.cammatch.repository.CameraRepository;
import com.cammatch.repository.FavoriteRepository;
import com.cammatch.repository.ForumCommentRepository;
import com.cammatch.repository.ForumPostRepository;
import com.cammatch.repository.UserCameraRepository;
import com.cammatch.repository.UserRepository;
import org.springframework.stereotype.Controller;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
@RequestMapping("/admin")
public class AdminController {
    private final CameraRepository cameraRepository;
    private final UserRepository userRepository;
    private final ForumPostRepository forumPostRepository;
    private final ForumCommentRepository forumCommentRepository;
    private final FavoriteRepository favoriteRepository;
    private final UserCameraRepository userCameraRepository;

    public AdminController(CameraRepository cameraRepository, UserRepository userRepository, ForumPostRepository forumPostRepository, ForumCommentRepository forumCommentRepository, FavoriteRepository favoriteRepository, UserCameraRepository userCameraRepository) {
        this.cameraRepository = cameraRepository;
        this.userRepository = userRepository;
        this.forumPostRepository = forumPostRepository;
        this.forumCommentRepository = forumCommentRepository;
        this.favoriteRepository = favoriteRepository;
        this.userCameraRepository = userCameraRepository;
    }

    @GetMapping
    public String index(Model model) {
        model.addAttribute("cameraCount", cameraRepository.count());
        model.addAttribute("userCount", userRepository.count());
        model.addAttribute("postCount", forumPostRepository.count());
        model.addAttribute("commentCount", forumCommentRepository.count());
        model.addAttribute("favoriteCount", favoriteRepository.count());
        return "admin/index";
    }

    @GetMapping("/cameras")
    public String cameras(Model model) {
        model.addAttribute("cameras", cameraRepository.findAllByOrderByBrandAscModelAsc());
        return "admin/cameras";
    }

    @GetMapping("/cameras/new")
    public String newCamera(Model model) {
        model.addAttribute("camera", new Camera());
        return "admin/camera-form";
    }

    @GetMapping("/cameras/{id}/edit")
    public String editCamera(@PathVariable Long id, Model model) {
        model.addAttribute("camera", cameraRepository.findById(id).orElseThrow());
        return "admin/camera-form";
    }

    @PostMapping("/cameras/save")
    public String saveCamera(@ModelAttribute Camera camera) {
        Camera value = camera;
        if (camera.getId() != null) {
            value = cameraRepository.findById(camera.getId()).orElseThrow();
            value.setBrand(camera.getBrand());
            value.setModel(camera.getModel());
            value.setType(camera.getType());
            value.setPhotographyType(camera.getPhotographyType());
            value.setPrice(camera.getPrice());
            value.setResolutionMp(camera.getResolutionMp());
            value.setBatteryShots(camera.getBatteryShots());
            value.setSensor(camera.getSensor());
            value.setVideo(camera.getVideo());
            value.setImageUrl(camera.getImageUrl());
            value.setDescription(camera.getDescription());
        }
        if (value.getAverageRating() == null) {
            value.setAverageRating(0.0);
        }
        if (value.getRatingCount() == null) {
            value.setRatingCount(0);
        }
        if (!isValidImageReference(value.getImageUrl())) {
            value.setImageUrl(imageForBrand(value.getBrand()));
        }
        cameraRepository.save(value);
        return "redirect:/admin/cameras?saved=true";
    }

    @PostMapping("/cameras/{id}/delete")
    @Transactional
    public String deleteCamera(@PathVariable Long id) {
        var camera = cameraRepository.findById(id).orElseThrow();

        userCameraRepository.findByPublicCamera(camera).forEach(userCamera -> {
            var owner = userCamera.getOwner();
            if (owner != null) {
                owner.setUserCamera(null);
                userRepository.save(owner);
            }
                userCamera.setPublicCamera(null);
            userCameraRepository.delete(userCamera);
        });
        userCameraRepository.flush();

        favoriteRepository.deleteByCamera(camera);
        cameraRepository.delete(camera);
        return "redirect:/admin/cameras?deleted=true";
    }

    @GetMapping("/users")
    public String users(Model model) {
        model.addAttribute("users", userRepository.findAll());
        return "admin/users";
    }

    @PostMapping("/users/{id}/toggle")
    public String toggleUser(@PathVariable Long id) {
        var user = userRepository.findById(id).orElseThrow();
        user.setActive(!user.isActive());
        userRepository.save(user);
        return "redirect:/admin/users?updated=true";
    }

    @GetMapping("/forum")
    public String forum(Model model) {
        model.addAttribute("posts", forumPostRepository.findAllByOrderByCreatedAtDesc());
        model.addAttribute("comments", forumCommentRepository.findAllByOrderByCreatedAtDesc());
        return "admin/forum";
    }

    @PostMapping("/forum/posts/{id}/toggle")
    public String togglePost(@PathVariable Long id) {
        var post = forumPostRepository.findById(id).orElseThrow();
        post.setApproved(!post.isApproved());
        forumPostRepository.save(post);
        return "redirect:/admin/forum?updated=true";
    }

    @PostMapping("/forum/posts/{id}/delete")
    public String deletePost(@PathVariable Long id) {
        forumPostRepository.deleteById(id);
        return "redirect:/admin/forum?deleted=true";
    }

    @PostMapping("/forum/comments/{id}/toggle")
    public String toggleComment(@PathVariable Long id) {
        var comment = forumCommentRepository.findById(id).orElseThrow();
        comment.setApproved(!comment.isApproved());
        forumCommentRepository.save(comment);
        return "redirect:/admin/forum?updated=true";
    }

    @PostMapping("/forum/comments/{id}/delete")
    public String deleteComment(@PathVariable Long id) {
        forumCommentRepository.deleteById(id);
        return "redirect:/admin/forum?deleted=true";
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