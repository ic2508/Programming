package com.cammatch.entity;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.ManyToOne;
import jakarta.persistence.Table;

import java.math.BigDecimal;
import java.time.LocalDateTime;

@Entity
@Table(name = "search_history")
public class SearchHistory {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToOne
    @JoinColumn(name = "user_id", nullable = false)
    private UserAccount user;

    @Column(precision = 10, scale = 2)
    private BigDecimal budget;

    @Column(length = 80)
    private String brand;

    @Column(length = 80)
    private String photographyType;

    private Double minResolution;

    private Integer minBattery;

    @Column(length = 40)
    private String sortBy;

    private LocalDateTime createdAt = LocalDateTime.now();

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public UserAccount getUser() {
        return user;
    }

    public void setUser(UserAccount user) {
        this.user = user;
    }

    public BigDecimal getBudget() {
        return budget;
    }

    public void setBudget(BigDecimal budget) {
        this.budget = budget;
    }

    public String getBrand() {
        return brand;
    }

    public void setBrand(String brand) {
        this.brand = brand;
    }

    public String getPhotographyType() {
        return photographyType;
    }

    public void setPhotographyType(String photographyType) {
        this.photographyType = photographyType;
    }

    public Double getMinResolution() {
        return minResolution;
    }

    public void setMinResolution(Double minResolution) {
        this.minResolution = minResolution;
    }

    public Integer getMinBattery() {
        return minBattery;
    }

    public void setMinBattery(Integer minBattery) {
        this.minBattery = minBattery;
    }

    public String getSortBy() {
        return sortBy;
    }

    public void setSortBy(String sortBy) {
        this.sortBy = sortBy;
    }

    public LocalDateTime getCreatedAt() {
        return createdAt;
    }

    public void setCreatedAt(LocalDateTime createdAt) {
        this.createdAt = createdAt;
    }
}
