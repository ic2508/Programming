package com.cammatch.service;

import com.cammatch.entity.Camera;
import com.cammatch.repository.CameraRepository;
import org.springframework.stereotype.Service;

import java.math.BigDecimal;
import java.util.Comparator;
import java.util.List;

@Service
public class RecommendationService {
    private final CameraRepository cameraRepository;

    public RecommendationService(CameraRepository cameraRepository) {
        this.cameraRepository = cameraRepository;
    }

    public List<RecommendationResult> recommend(BigDecimal budget, String brand, String photographyType, Double minResolution, Integer minBattery) {
        return recommend(budget, brand, photographyType, minResolution, minBattery, "score_desc");
    }

    public List<RecommendationResult> recommend(BigDecimal budget, String brand, String photographyType, Double minResolution, Integer minBattery, String sortBy) {
        Comparator<RecommendationResult> comparator = switch (sortBy == null ? "score_desc" : sortBy) {
            case "price_asc" -> Comparator.comparing(result -> result.getCamera().getPrice());
            case "price_desc" -> Comparator.comparing((RecommendationResult result) -> result.getCamera().getPrice()).reversed();
            case "resolution_desc" -> Comparator.comparing((RecommendationResult result) -> result.getCamera().getResolutionMp()).reversed();
            case "battery_desc" -> Comparator.comparing((RecommendationResult result) -> result.getCamera().getBatteryShots()).reversed();
            case "rating_desc" -> Comparator.comparing((RecommendationResult result) -> result.getCamera().getAverageRating()).reversed();
            default -> Comparator.comparingInt(RecommendationResult::getScore).reversed();
        };
        return cameraRepository.findAllByOrderByBrandAscModelAsc()
                .stream()
                .map(camera -> score(camera, budget, brand, photographyType, minResolution, minBattery))
                .filter(result -> result.getScore() > 0)
                .sorted(comparator)
                .toList();
    }

    private RecommendationResult score(Camera camera, BigDecimal budget, String brand, String photographyType, Double minResolution, Integer minBattery) {
        int score = 0;
        StringBuilder reason = new StringBuilder();

        if (budget != null) {
            if (camera.getPrice().compareTo(budget) <= 0) {
                score += 30;
                reason.append("se incadreaza in buget; ");
            } else {
                score -= 40;
            }
        }

        if (brand != null && !brand.isBlank()) {
            if (camera.getBrand().equalsIgnoreCase(brand.trim())) {
                score += 20;
                reason.append("brand preferat; ");
            } else {
                score -= 10;
            }
        }

        if (photographyType != null && !photographyType.isBlank()) {
            if (camera.getPhotographyType().equalsIgnoreCase(photographyType.trim())) {
                score += 25;
                reason.append("potrivita pentru tipul de fotografie ales; ");
            }
        }

        if (minResolution != null) {
            if (camera.getResolutionMp() >= minResolution) {
                score += 15;
                reason.append("rezolutie suficienta; ");
            } else {
                score -= 10;
            }
        }

        if (minBattery != null) {
            if (camera.getBatteryShots() >= minBattery) {
                score += 10;
                reason.append("autonomie buna; ");
            } else {
                score -= 8;
            }
        }

        if (budget == null && (brand == null || brand.isBlank()) && (photographyType == null || photographyType.isBlank()) && minResolution == null && minBattery == null) {
            score = 50;
            reason.append("recomandare generala; ");
        }

        if (reason.isEmpty()) {
            reason.append("potrivire partiala; ");
        }

        return new RecommendationResult(camera, Math.max(score, 0), reason.toString());
    }
}
