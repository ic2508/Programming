package com.cammatch.repository;

import com.cammatch.entity.Camera;
import com.cammatch.entity.UserAccount;
import com.cammatch.entity.UserFavorite;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Collection;
import java.util.List;

public interface FavoriteRepository extends JpaRepository<UserFavorite, Long> {
    List<UserFavorite> findByUserOrderByCreatedAtDesc(UserAccount user);
    boolean existsByUserAndCamera(UserAccount user, Camera camera);
    long countByUser(UserAccount user);
    void deleteByUserAndCamera(UserAccount user, Camera camera);
    void deleteByCamera(Camera camera);
    void deleteByUserIn(Collection<UserAccount> users);
}
