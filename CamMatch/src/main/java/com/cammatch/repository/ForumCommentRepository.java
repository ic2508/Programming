package com.cammatch.repository;

import com.cammatch.entity.ForumComment;
import com.cammatch.entity.ForumPost;
import com.cammatch.entity.UserAccount;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.Collection;
import java.util.List;

public interface ForumCommentRepository extends JpaRepository<ForumComment, Long> {
    List<ForumComment> findByPostAndApprovedTrueOrderByCreatedAtAsc(ForumPost post);
    List<ForumComment> findAllByOrderByCreatedAtDesc();
    void deleteByAuthorIn(Collection<UserAccount> authors);
}
