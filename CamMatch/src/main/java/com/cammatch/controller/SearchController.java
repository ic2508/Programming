package com.cammatch.controller;

import com.cammatch.repository.CameraRepository;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class SearchController {
    private final CameraRepository cameraRepository;

    public SearchController(CameraRepository cameraRepository) {
        this.cameraRepository = cameraRepository;
    }

    @GetMapping("/search")
    public String search(@RequestParam(required = false) String q, Model model) {
        var results = q == null || q.isBlank()
                ? cameraRepository.findAllByOrderByBrandAscModelAsc()
                : cameraRepository.findByBrandContainingIgnoreCaseOrModelContainingIgnoreCaseOrderByBrandAscModelAsc(q, q);
        model.addAttribute("q", q);
        model.addAttribute("results", results);
        return "search";
    }
}
