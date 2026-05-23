package com.cammatch.service;

import com.cammatch.entity.Role;
import com.cammatch.entity.UserAccount;
import com.cammatch.repository.UserRepository;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Optional;
import java.util.UUID;

@Service
public class UserService {
    private final UserRepository userRepository;
    private final PasswordEncoder passwordEncoder;

    public UserService(UserRepository userRepository, PasswordEncoder passwordEncoder) {
        this.userRepository = userRepository;
        this.passwordEncoder = passwordEncoder;
    }

    @Transactional
    public UserAccount register(String username, String email, String password) {
        UserAccount user = new UserAccount();
        user.setUsername(username.trim());
        user.setEmail(email.trim().toLowerCase());
        user.setPassword(passwordEncoder.encode(password));
        user.setRole(Role.USER);
        user.setConfirmed(false);
        user.setActive(true);
        user.setConfirmationToken(UUID.randomUUID().toString());
        return userRepository.save(user);
    }

    @Transactional
    public boolean confirm(String token) {
        Optional<UserAccount> optionalUser = userRepository.findByConfirmationToken(token);
        if (optionalUser.isEmpty()) {
            return false;
        }
        UserAccount user = optionalUser.get();
        user.setConfirmed(true);
        user.setConfirmationToken(null);
        userRepository.save(user);
        return true;
    }

    @Transactional
    public Optional<UserAccount> createResetToken(String email) {
        Optional<UserAccount> optionalUser = userRepository.findByEmail(email.trim().toLowerCase());
        optionalUser.ifPresent(user -> {
            user.setResetToken(UUID.randomUUID().toString());
            userRepository.save(user);
        });
        return optionalUser;
    }

    @Transactional
    public boolean resetPassword(String token, String password) {
        Optional<UserAccount> optionalUser = userRepository.findByResetToken(token);
        if (optionalUser.isEmpty()) {
            return false;
        }
        UserAccount user = optionalUser.get();
        user.setPassword(passwordEncoder.encode(password));
        user.setResetToken(null);
        userRepository.save(user);
        return true;
    }
}
