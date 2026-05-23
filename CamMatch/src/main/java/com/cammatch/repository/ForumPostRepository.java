package com.cammatch.repository;

import com.cammatch.entity.Camera;
import com.cammatch.entity.ForumPost;
import com.cammatch.entity.UserAccount;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Collection;
import java.util.List;

public interface ForumPostRepository extends JpaRepository<ForumPost, Long> {
    List<ForumPost> findByCameraAndApprovedTrueOrderByCreatedAtDesc(Camera camera);
    List<ForumPost> findAllByOrderByCreatedAtDesc();
    List<ForumPost> findByAuthorIn(Collection<UserAccount> authors);
}
