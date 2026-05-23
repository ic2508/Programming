package com.cammatch.controller;

import com.cammatch.repository.CameraRepository;
import com.cammatch.repository.FavoriteRepository;
import com.cammatch.repository.SearchHistoryRepository;
import com.cammatch.repository.UserRepository;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import java.security.Principal;

@Controller
public class HomeController {
    private final CameraRepository cameraRepository;
    private final UserRepository userRepository;
    private final FavoriteRepository favoriteRepository;
    private final SearchHistoryRepository searchHistoryRepository;

    public HomeController(CameraRepository cameraRepository, UserRepository userRepository, FavoriteRepository favoriteRepository, SearchHistoryRepository searchHistoryRepository) {
        this.cameraRepository = cameraRepository;
        this.userRepository = userRepository;
        this.favoriteRepository = favoriteRepository;
        this.searchHistoryRepository = searchHistoryRepository;
    }

    @GetMapping("/")
    public String index(Model model) {
        model.addAttribute("cameraCount", cameraRepository.count());
        model.addAttribute("featuredCameras", cameraRepository.findAllByOrderByBrandAscModelAsc().stream().limit(3).toList());
        return "index";
    }

    @GetMapping("/dashboard")
    public String dashboard(Principal principal, Model model) {
        model.addAttribute("cameraCount", cameraRepository.count());
        model.addAttribute("latestCameras", cameraRepository.findAllByOrderByBrandAscModelAsc().stream().limit(6).toList());
        if (principal != null) {
            var user = userRepository.findByEmail(principal.getName()).orElseThrow();
            model.addAttribute("user", user);
            model.addAttribute("favoriteCount", favoriteRepository.countByUser(user));
            model.addAttribute("searchCount", searchHistoryRepository.countByUser(user));
        }
        return "dashboard";
    }
}
