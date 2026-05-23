package com.cammatch.entity;

import jakarta.persistence.CascadeType;
import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.OneToMany;
import jakarta.persistence.Table;
import jakarta.validation.constraints.DecimalMin;
import jakarta.validation.constraints.Min;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;

import java.math.BigDecimal;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

@Entity
@Table(name = "cameras")
public class Camera {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @NotBlank
    @Column(nullable = false, length = 80)
    private String brand;

    @NotBlank
    @Column(nullable = false, length = 120)
    private String model;

    @NotBlank
    @Column(nullable = false, length = 80)
    private String type;

    @NotBlank
    @Column(nullable = false, length = 80)
    private String photographyType;

    @NotNull
    @DecimalMin("0.0")
    @Column(nullable = false, precision = 10, scale = 2)
    private BigDecimal price;

    @NotNull
    @DecimalMin("1.0")
    @Column(nullable = false)
    private Double resolutionMp;

    @NotNull
    @Min(1)
    @Column(nullable = false)
    private Integer batteryShots;

    @Column(length = 80)
    private String sensor;

    @Column(length = 80)
    private String video;

    @Column(length = 500)
    private String imageUrl;

    @Column(nullable = false)
    private Double averageRating = 0.0;

    @Column(nullable = false)
    private Integer ratingCount = 0;

    @Column(length = 1500)
    private String description;

    private LocalDateTime createdAt = LocalDateTime.now();

    @OneToMany(mappedBy = "camera", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<ForumPost> forumPosts = new ArrayList<>();

    @OneToMany(mappedBy = "camera", cascade = CascadeType.ALL, orphanRemoval = true)
    private List<CameraRating> ratings = new ArrayList<>();

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getBrand() {
        return brand;
    }

    public void setBrand(String brand) {
        this.brand = brand;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getPhotographyType() {
        return photographyType;
    }

    public void setPhotographyType(String photographyType) {
        this.photographyType = photographyType;
    }

    public BigDecimal getPrice() {
        return price;
    }

    public void setPrice(BigDecimal price) {
        this.price = price;
    }

    public Double getResolutionMp() {
        return resolutionMp;
    }

    public void setResolutionMp(Double resolutionMp) {
        this.resolutionMp = resolutionMp;
    }

    public Integer getBatteryShots() {
        return batteryShots;
    }

    public void setBatteryShots(Integer batteryShots) {
        this.batteryShots = batteryShots;
    }

    public String getSensor() {
        return sensor;
    }

    public void setSensor(String sensor) {
        this.sensor = sensor;
    }

    public String getVideo() {
        return video;
    }

    public void setVideo(String video) {
        this.video = video;
    }

    public String getImageUrl() {
        return imageUrl;
    }

    public void setImageUrl(String imageUrl) {
        this.imageUrl = imageUrl;
    }

    public Double getAverageRating() {
        return averageRating;
    }

    public void setAverageRating(Double averageRating) {
        this.averageRating = averageRating == null ? 0.0 : averageRating;
    }

    public Integer getRatingCount() {
        return ratingCount;
    }

    public void setRatingCount(Integer ratingCount) {
        this.ratingCount = ratingCount == null ? 0 : ratingCount;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public LocalDateTime getCreatedAt() {
        return createdAt;
    }

    public void setCreatedAt(LocalDateTime createdAt) {
        this.createdAt = createdAt == null ? LocalDateTime.now() : createdAt;
    }

    public List<ForumPost> getForumPosts() {
        return forumPosts;
    }

    public void setForumPosts(List<ForumPost> forumPosts) {
        this.forumPosts = forumPosts;
    }

    public List<CameraRating> getRatings() {
        return ratings;
    }

    public void setRatings(List<CameraRating> ratings) {
        this.ratings = ratings;
    }

    public String getFullName() {
        return brand + " " + model;
    }

    public String getRatingLabel() {
        if (ratingCount == null || ratingCount == 0) {
            return "Not rated";
        }
        double value = averageRating == null ? 0.0 : averageRating;
        return String.format(Locale.US, "%.2f / 5", value);
    }

    public double getStarPercent() {
        if (ratingCount == null || ratingCount == 0 || averageRating == null) {
            return 0.0;
        }
        double value = Math.max(0.0, Math.min(5.0, averageRating));
        return value * 20.0;
    }
}
