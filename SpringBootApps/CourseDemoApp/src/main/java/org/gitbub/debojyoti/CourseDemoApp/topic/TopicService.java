package org.gitbub.debojyoti.CourseDemoApp.topic;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@Service
public class TopicService {
    private List<Topic> topicRepository;

    @Autowired
    private TopicRepository repository;

    public TopicService() {
    }

    public List<Topic> getAllTopics() {
        // Should be able to add pagination on this one
        List<Topic> returnValue = new ArrayList<>();
        for (Topic topic : repository.findAll()) {
            returnValue.add(topic);
        }

        return returnValue;
    }

    public Optional<Topic> getTopic(String id) {
        return repository.findById(id);
    }

    public Topic add(Topic newTopic) {
        return repository.save(newTopic);
    }

    public Topic updateTopic(Topic t) {
        return repository.save(t);
    }

    public void deleteTopic(String Id) {
        repository.deleteById(Id);
    }
}
