package org.gitbub.debojyoti.CourseDemoApp.topic;

import org.springframework.stereotype.Service;

import java.util.Arrays;
import java.util.List;
import java.util.Optional;

@Service
public class TopicService {

    private List<Topic> topics = Arrays.asList(
            new Topic("1", "Machine Learning", "Has a path for machine learning items"),
            new Topic("2", "Windows System Programming", "Windows kernel programming and stuff"),
            new Topic("3", "Spring Boot", "A definitive resource for all spring related items")
    );

    public List<Topic> getAllTopics() {
        return topics;
    }

    public Optional<Topic> getTopic(String id) {
        return topics.stream().filter(t -> t.getId().equals(id)).findFirst();
    }
}
