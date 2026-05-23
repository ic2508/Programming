package com.cammatch.controller;

import com.cammatch.entity.UserFavorite;
import com.cammatch.repository.CameraRepository;
import com.cammatch.repository.FavoriteRepository;
import com.cammatch.repository.UserRepository;
import jakarta.servlet.http.HttpServletRequest;
import org.springframework.stereotype.Controller;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;

import java.security.Principal;

@Controller
public class FavoriteController {
    private final FavoriteRepository favoriteRepository;
    private final CameraRepository cameraRepository;
    private final UserRepository userRepository;

    public FavoriteController(FavoriteRepository favoriteRepository, CameraRepository cameraRepository, UserRepository userRepository) {
        this.favoriteRepository = favoriteRepository;
        this.cameraRepository = cameraRepository;
        this.userRepository = userRepository;
    }

    @GetMapping("/favorites")
    public String favorites(Principal principal, Model model) {
        var user = userRepository.findByEmail(principal.getName()).orElseThrow();
        model.addAttribute("favorites", favoriteRepository.findByUserOrderByCreatedAtDesc(user));
        return "favorites";
    }

    @PostMapping("/favorites/{cameraId}/toggle")
    @Transactional
    public String toggle(@PathVariable Long cameraId, Principal principal, HttpServletRequest request) {
        var user = userRepository.findByEmail(principal.getName()).orElseThrow();
        var camera = cameraRepository.findById(cameraId).orElseThrow();
        if (favoriteRepository.existsByUserAndCamera(user, camera)) {
            favoriteRepository.deleteByUserAndCamera(user, camera);
        } else {
            UserFavorite favorite = new UserFavorite();
            favorite.setUser(user);
            favorite.setCamera(camera);
            favoriteRepository.save(favorite);
        }
        String referer = request.getHeader("Referer");
        if (referer != null && !referer.isBlank()) {
            return "redirect:" + referer;
        }
        return "redirect:/cameras/" + cameraId;
    }
}
