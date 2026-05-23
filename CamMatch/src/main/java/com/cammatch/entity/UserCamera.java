package com.cammatch.entity;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.OneToOne;
import jakarta.persistence.Table;

import java.math.BigDecimal;

@Entity
@Table(name = "user_cameras")
public class UserCamera {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @OneToOne
    @JoinColumn(name = "owner_id", nullable = false, unique = true)
    private UserAccount owner;

    @OneToOne
    @JoinColumn(name = "public_camera_id")
    private Camera publicCamera;

    @Column(nullable = false, length = 80)
    private String brand;

    @Column(nullable = false, length = 120)
    private String model;

    @Column(length = 80)
    private String type;

    @Column(length = 80)
    private String photographyType;

    private Double resolutionMp;

    private Integer batteryShots;

    @Column(length = 80)
    private String sensor;

    @Column(length = 80)
    private String video;

    @Column(precision = 10, scale = 2)
    private BigDecimal price;

    @Column(length = 500)
    private String imageUrl;

    @Column(length = 1000)
    private String notes;

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public UserAccount getOwner() {
        return owner;
    }

    public void setOwner(UserAccount owner) {
        this.owner = owner;
    }

    public Camera getPublicCamera() {
        return publicCamera;
    }

    public void setPublicCamera(Camera publicCamera) {
        this.publicCamera = publicCamera;
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

    public BigDecimal getPrice() {
        return price;
    }

    public void setPrice(BigDecimal price) {
        this.price = price;
    }

    public String getImageUrl() {
        return imageUrl;
    }

    public void setImageUrl(String imageUrl) {
        this.imageUrl = imageUrl;
    }

    public String getNotes() {
        return notes;
    }

    public void setNotes(String notes) {
        this.notes = notes;
    }
}
