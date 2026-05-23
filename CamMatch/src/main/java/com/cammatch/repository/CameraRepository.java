package com.cammatch.repository;

import com.cammatch.entity.Camera;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;
import java.util.Optional;

public interface CameraRepository extends JpaRepository<Camera, Long> {
    List<Camera> findAllByOrderByBrandAscModelAsc();
    List<Camera> findByBrandContainingIgnoreCaseOrModelContainingIgnoreCaseOrderByBrandAscModelAsc(String brand, String model);
    Optional<Camera> findByBrandIgnoreCaseAndModelIgnoreCase(String brand, String model);
}
