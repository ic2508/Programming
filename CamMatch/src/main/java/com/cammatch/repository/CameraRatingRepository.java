package com.cammatch.repository;

import com.cammatch.entity.Camera;
import com.cammatch.entity.CameraRating;
import com.cammatch.entity.UserAccount;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Collection;
import java.util.List;
import java.util.Optional;

public interface CameraRatingRepository extends JpaRepository<CameraRating, Long> {
    Optional<CameraRating> findByCameraAndUser(Camera camera, UserAccount user);
    List<CameraRating> findByCamera(Camera camera);
    void deleteByUserIn(Collection<UserAccount> users);
}
