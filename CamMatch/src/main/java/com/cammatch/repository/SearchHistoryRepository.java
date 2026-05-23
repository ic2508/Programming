package com.cammatch.repository;

import com.cammatch.entity.SearchHistory;
import com.cammatch.entity.UserAccount;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface SearchHistoryRepository extends JpaRepository<SearchHistory, Long> {
    List<SearchHistory> findTop5ByUserOrderByCreatedAtDesc(UserAccount user);
    List<SearchHistory> findByUserOrderByCreatedAtDesc(UserAccount user);
    long countByUser(UserAccount user);
}
