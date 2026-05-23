package com.cammatch.service;

import com.cammatch.entity.Camera;

public class RecommendationResult {
    private final Camera camera;
    private final int score;
    private final String reason;

    public RecommendationResult(Camera camera, int score, String reason) {
        this.camera = camera;
        this.score = score;
        this.reason = reason;
    }

    public Camera getCamera() {
        return camera;
    }

    public int getScore() {
        return score;
    }

    public String getReason() {
        return reason;
    }
}
