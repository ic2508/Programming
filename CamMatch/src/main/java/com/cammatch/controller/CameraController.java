package com.cammatch.controller;

import com.cammatch.entity.Camera;
import com.cammatch.entity.CameraRating;
import com.cammatch.entity.ForumComment;
import com.cammatch.repository.CameraRatingRepository;
import com.cammatch.repository.CameraRepository;
import com.cammatch.repository.FavoriteRepository;
import com.cammatch.repository.ForumCommentRepository;
import com.cammatch.repository.ForumPostRepository;
import com.cammatch.repository.UserRepository;
import org.springframework.stereotype.Controller;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

import java.security.Principal;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

@Controller
public class CameraController {
    private final CameraRepository cameraRepository;
    private final CameraRatingRepository cameraRatingRepository;
    private final ForumPostRepository forumPostRepository;
    private final ForumCommentRepository forumCommentRepository;
    private final FavoriteRepository favoriteRepository;
    private final UserRepository userRepository;

    public CameraController(CameraRepository cameraRepository, CameraRatingRepository cameraRatingRepository, ForumPostRepository forumPostRepository, ForumCommentRepository forumCommentRepository, FavoriteRepository favoriteRepository, UserRepository userRepository) {
        this.cameraRepository = cameraRepository;
        this.cameraRatingRepository = cameraRatingRepository;
        this.forumPostRepository = forumPostRepository;
        this.forumCommentRepository = forumCommentRepository;
        this.favoriteRepository = favoriteRepository;
        this.userRepository = userRepository;
    }

    @GetMapping("/cameras")
    public String cameras(@RequestParam(required = false) String q, Model model) {
        List<Camera> cameras;
        if (q != null && !q.isBlank()) {
            cameras = cameraRepository.findByBrandContainingIgnoreCaseOrModelContainingIgnoreCaseOrderByBrandAscModelAsc(q, q);
        } else {
            cameras = cameraRepository.findAllByOrderByBrandAscModelAsc();
        }
        model.addAttribute("cameras", cameras);
        model.addAttribute("q", q);
        return "cameras/list";
    }

    @GetMapping("/cameras/{id}")
    public String details(@PathVariable Long id, Principal principal, Model model) {
        Camera camera = cameraRepository.findById(id).orElseThrow();
        var posts = forumPostRepository.findByCameraAndApprovedTrueOrderByCreatedAtDesc(camera);
        Map<Long, List<ForumComment>> commentsByPost = new LinkedHashMap<>();
        posts.forEach(post -> commentsByPost.put(post.getId(), forumCommentRepository.findByPostAndApprovedTrueOrderByCreatedAtAsc(post)));
        boolean favorite = false;
        Integer userRating = null;
        if (principal != null) {
            var user = userRepository.findByEmail(principal.getName()).orElseThrow();
            favorite = favoriteRepository.existsByUserAndCamera(user, camera);
            userRating = cameraRatingRepository.findByCameraAndUser(camera, user).map(CameraRating::getStars).orElse(null);
        }
        model.addAttribute("camera", camera);
        model.addAttribute("posts", posts);
        model.addAttribute("commentsByPost", commentsByPost);
        model.addAttribute("favorite", favorite);
        model.addAttribute("userRating", userRating);
        return "cameras/details";
    }

    @PostMapping("/cameras/{id}/rating")
    @Transactional
    public String rateCamera(@PathVariable Long id, @RequestParam Integer stars, Principal principal) {
        if (principal == null) {
            return "redirect:/login";
        }
        Camera camera = cameraRepository.findById(id).orElseThrow();
        var user = userRepository.findByEmail(principal.getName()).orElseThrow();
        int safeStars = Math.max(1, Math.min(5, stars == null ? 0 : stars));
        CameraRating rating = cameraRatingRepository.findByCameraAndUser(camera, user).orElseGet(CameraRating::new);
        rating.setCamera(camera);
        rating.setUser(user);
        rating.setStars(safeStars);
        cameraRatingRepository.save(rating);
        updateCameraAverage(camera);
        return "redirect:/cameras/" + id + "?rated=true";
    }

    @GetMapping("/compare")
    public String compare(@RequestParam(required = false) List<Long> ids, Model model) {
        List<Camera> selected = new ArrayList<>();
        if (ids != null) {
            selected = cameraRepository.findAllById(ids);
        }
        model.addAttribute("allCameras", cameraRepository.findAllByOrderByBrandAscModelAsc());
        model.addAttribute("selected", selected);
        model.addAttribute("ids", ids == null ? List.of() : ids);
        return "cameras/compare";
    }

    private void updateCameraAverage(Camera camera) {
        List<CameraRating> ratings = cameraRatingRepository.findByCamera(camera);
        if (ratings.isEmpty()) {
            camera.setAverageRating(0.0);
            camera.setRatingCount(0);
        } else {
            double average = ratings.stream().mapToInt(CameraRating::getStars).average().orElse(0.0);
            camera.setAverageRating(Math.round(average * 100.0) / 100.0);
            camera.setRatingCount(ratings.size());
        }
        cameraRepository.save(camera);
    }
}
