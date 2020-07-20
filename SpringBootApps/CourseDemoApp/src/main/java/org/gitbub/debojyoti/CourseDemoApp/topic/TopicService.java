package org.gitbub.debojyoti.CourseDemoApp.topic;

import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@Service
public class TopicService {
    private List<Topic> topicRepository;

    public TopicService() {
        topicRepository = new ArrayList<>();

        // Adding mock data
        topicRepository.add(new Topic("1", "C/C++", "You don't need it but you will end up using it "));
        topicRepository.add(new Topic("2", "Java", "Very handy to learn this"));
        topicRepository.add((new Topic("3","C#","If you have ever used Windows must need it")));
    }

    public List<Topic> getAllTopics() {
        return topicRepository;
    }

    public Optional<Topic> getTopic(String id) {
        return topicRepository.stream().filter(t -> t.getId().equals(id)).findFirst();
    }

    public boolean add(Topic newTopic) {
        String newId = newTopic.getId();

        // The Id should be a new item
        Optional<Topic> existingTopic = topicRepository.stream()
                .filter(t -> t.getId().equals(newId))
                .findFirst();
        if( existingTopic.isPresent() ) return false;

        topicRepository.add(newTopic);
        return true;
    }

    public boolean updateTopic(Topic t) {
        boolean retValue = false;

        // Going through each item, must be a better way to use lambda expression
        for( Topic topic : topicRepository) {
            // If there is a match with ID
            if( topic.getId().equals(t.getId())) {
                // Updating the object
                topic.setCaption(t.getCaption());
                topic.setDescription(t.getDescription());

                // Breaking the find
                retValue = true;
                break;
            }
        }

        return retValue;
    }

    // Simple delete operation
    public boolean deleteTopic(String Id) {
        return topicRepository.removeIf(t -> t.getId().equals(Id));
    }
}
