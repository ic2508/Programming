package com.cammatch.repository;

import com.cammatch.entity.Camera;
import com.cammatch.entity.UserAccount;
import com.cammatch.entity.UserCamera;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;
import java.util.Optional;

public interface UserCameraRepository extends JpaRepository<UserCamera, Long> {
    Optional<UserCamera> findByOwner(UserAccount owner);
    List<UserCamera> findByPublicCamera(Camera publicCamera);
}
