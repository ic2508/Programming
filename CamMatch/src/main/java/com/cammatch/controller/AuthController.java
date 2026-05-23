package com.cammatch.controller;

import com.cammatch.repository.UserRepository;
import com.cammatch.service.UserService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class AuthController {
    private final UserRepository userRepository;
    private final UserService userService;

    public AuthController(UserRepository userRepository, UserService userService) {
        this.userRepository = userRepository;
        this.userService = userService;
    }

    @GetMapping("/login")
    public String login() {
        return "auth/login";
    }

    @GetMapping("/register")
    public String registerForm() {
        return "auth/register";
    }

    @PostMapping("/register")
    public String register(@RequestParam String username, @RequestParam String email, @RequestParam String password, Model model) {
        if (username == null || username.trim().length() < 3 || email == null || email.isBlank() || !isStrongPassword(password)) {
            model.addAttribute("error", "Username-ul trebuie sa aiba minimum 3 caractere. Parola trebuie sa aiba minimum 6 caractere, litere, cifre si un caracter special.");
            return "auth/register";
        }
        if (userRepository.existsByUsername(username.trim())) {
            model.addAttribute("error", "Username-ul este deja folosit.");
            return "auth/register";
        }
        if (userRepository.existsByEmail(email.trim().toLowerCase())) {
            model.addAttribute("error", "Email-ul este deja folosit.");
            return "auth/register";
        }
        var user = userService.register(username, email, password);
        model.addAttribute("confirmLink", "/confirm?token=" + user.getConfirmationToken());
        return "auth/confirm-sent";
    }

    @GetMapping("/confirm")
    public String confirm(@RequestParam String token, Model model) {
        boolean success = userService.confirm(token);
        model.addAttribute("success", success);
        return "auth/confirm-result";
    }

    @GetMapping("/forgot-password")
    public String forgotPasswordForm() {
        return "auth/forgot-password";
    }

    @PostMapping("/forgot-password")
    public String forgotPassword(@RequestParam String email, Model model) {
        var user = userService.createResetToken(email);
        user.ifPresent(value -> model.addAttribute("resetLink", "/reset-password?token=" + value.getResetToken()));
        model.addAttribute("sent", true);
        return "auth/forgot-password";
    }

    @GetMapping("/reset-password")
    public String resetPasswordForm(@RequestParam String token, Model model) {
        model.addAttribute("token", token);
        return "auth/reset-password";
    }

    @PostMapping("/reset-password")
    public String resetPassword(@RequestParam String token, @RequestParam String password, Model model) {
        if (!isStrongPassword(password)) {
            model.addAttribute("token", token);
            model.addAttribute("error", "Parola trebuie sa aiba minimum 6 caractere, litere, cifre si un caracter special.");
            return "auth/reset-password";
        }
        boolean success = userService.resetPassword(token, password);
        model.addAttribute("success", success);
        return "auth/reset-result";
    }

    private boolean isStrongPassword(String password) {
        if (password == null || password.length() < 6) {
            return false;
        }
        boolean hasLetter = password.matches(".*[A-Za-z].*");
        boolean hasDigit = password.matches(".*\\d.*");
        boolean hasSpecial = password.matches(".*[^A-Za-z0-9].*");
        return hasLetter && hasDigit && hasSpecial;
    }
}
