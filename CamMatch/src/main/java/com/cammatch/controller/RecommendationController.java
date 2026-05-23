package com.cammatch.controller;

import com.cammatch.entity.SearchHistory;
import com.cammatch.repository.CameraRepository;
import com.cammatch.repository.SearchHistoryRepository;
import com.cammatch.repository.UserRepository;
import com.cammatch.service.RecommendationService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

import java.math.BigDecimal;
import java.security.Principal;

@Controller
public class RecommendationController {
    private final RecommendationService recommendationService;
    private final CameraRepository cameraRepository;
    private final UserRepository userRepository;
    private final SearchHistoryRepository searchHistoryRepository;

    public RecommendationController(RecommendationService recommendationService, CameraRepository cameraRepository, UserRepository userRepository, SearchHistoryRepository searchHistoryRepository) {
        this.recommendationService = recommendationService;
        this.cameraRepository = cameraRepository;
        this.userRepository = userRepository;
        this.searchHistoryRepository = searchHistoryRepository;
    }

    @GetMapping("/recommendations")
    public String form(Model model) {
        addOptions(model);
        return "recommendations";
    }

    @PostMapping("/recommendations")
    public String recommend(@RequestParam(required = false) BigDecimal budget,
                            @RequestParam(required = false) String brand,
                            @RequestParam(required = false) String photographyType,
                            @RequestParam(required = false) Double minResolution,
                            @RequestParam(required = false) Integer minBattery,
                            @RequestParam(required = false, defaultValue = "score_desc") String sortBy,
                            Principal principal,
                            Model model) {
        model.addAttribute("results", recommendationService.recommend(budget, brand, photographyType, minResolution, minBattery, sortBy));
        model.addAttribute("budget", budget);
        model.addAttribute("brand", brand);
        model.addAttribute("photographyType", photographyType);
        model.addAttribute("minResolution", minResolution);
        model.addAttribute("minBattery", minBattery);
        model.addAttribute("sortBy", sortBy);
        if (principal != null) {
            var user = userRepository.findByEmail(principal.getName()).orElseThrow();
            SearchHistory history = new SearchHistory();
            history.setUser(user);
            history.setBudget(budget);
            history.setBrand(blankToNull(brand));
            history.setPhotographyType(blankToNull(photographyType));
            history.setMinResolution(minResolution);
            history.setMinBattery(minBattery);
            history.setSortBy(sortBy);
            searchHistoryRepository.save(history);
        }
        addOptions(model);
        return "recommendations";
    }

    private void addOptions(Model model) {
        var cameras = cameraRepository.findAllByOrderByBrandAscModelAsc();
        model.addAttribute("brands", cameras.stream().map(camera -> camera.getBrand()).distinct().toList());
        model.addAttribute("types", cameras.stream().map(camera -> camera.getPhotographyType()).distinct().toList());
    }

    private String blankToNull(String value) {
        return value == null || value.isBlank() ? null : value.trim();
    }
}
