package com.cammatch.controller;

import com.cammatch.entity.ForumComment;
import com.cammatch.entity.ForumPost;
import com.cammatch.entity.UserAccount;
import com.cammatch.repository.CameraRepository;
import com.cammatch.repository.ForumCommentRepository;
import com.cammatch.repository.ForumPostRepository;
import com.cammatch.repository.UserRepository;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

import java.security.Principal;

@Controller
public class ForumController {
    private final CameraRepository cameraRepository;
    private final ForumPostRepository forumPostRepository;
    private final ForumCommentRepository forumCommentRepository;
    private final UserRepository userRepository;

    public ForumController(CameraRepository cameraRepository, ForumPostRepository forumPostRepository, ForumCommentRepository forumCommentRepository, UserRepository userRepository) {
        this.cameraRepository = cameraRepository;
        this.forumPostRepository = forumPostRepository;
        this.forumCommentRepository = forumCommentRepository;
        this.userRepository = userRepository;
    }

    @PostMapping("/forum/camera/{cameraId}/posts")
    public String createPost(@PathVariable Long cameraId, @RequestParam String title, @RequestParam String content, Principal principal) {
        if (title == null || title.isBlank() || content == null || content.isBlank()) {
            return "redirect:/cameras/" + cameraId + "?postError=true";
        }
        var camera = cameraRepository.findById(cameraId).orElseThrow();
        ForumPost post = new ForumPost();
        post.setCamera(camera);
        post.setAuthor(currentUser(principal));
        post.setTitle(title.trim());
        post.setContent(content.trim());
        forumPostRepository.save(post);
        return "redirect:/cameras/" + cameraId + "?postCreated=true";
    }

    @PostMapping("/forum/posts/{postId}/comments")
    public String createComment(@PathVariable Long postId, @RequestParam String content, Principal principal) {
        var post = forumPostRepository.findById(postId).orElseThrow();
        if (content == null || content.isBlank()) {
            return "redirect:/cameras/" + post.getCamera().getId() + "?commentError=true";
        }
        ForumComment comment = new ForumComment();
        comment.setPost(post);
        comment.setAuthor(currentUser(principal));
        comment.setContent(content.trim());
        forumCommentRepository.save(comment);
        return "redirect:/cameras/" + post.getCamera().getId() + "?commentCreated=true";
    }

    private UserAccount currentUser(Principal principal) {
        return userRepository.findByEmail(principal.getName()).orElseThrow();
    }
}
