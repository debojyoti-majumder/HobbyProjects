package org.gitbub.debojyoti.CourseDemoApp.topic;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.web.bind.annotation.*;

import org.springframework.http.HttpStatus;
import org.springframework.web.server.ResponseStatusException;

import java.util.List;

@RestController
public class TopicController {

    @Autowired
    private TopicService topicService;
    private static final Logger logger = LoggerFactory.getLogger(TopicController.class);

    // By default it is a mapping for a get request
    @GetMapping("/api/topics")
    public List<Topic> getAllTopics() {
        logger.info("Listing all the topics");
        return topicService.getAllTopics();
    }

    @GetMapping("/api/topics/{topicID}")
    public Topic getTopicWithId(@PathVariable("topicID") Integer id) {
        logger.info("Getting topic with Topic ID " + id);

        // As the return type of the service is Optional may be there is check required to report error
        var findResult = topicService.getTopic(id);

        // Throwing an exception in case no topic found
        if( findResult.isEmpty() ) {
            var errorMessage = "Not found topic with ID:"+ id;
            logger.warn(errorMessage);
            throw new ResponseStatusException(HttpStatus.NOT_FOUND, errorMessage);
        }

        // Returning the result
        return findResult.get();
    }

    @PostMapping("/api/topics")
    public void postTopic(@RequestBody Topic newTopic) {
        var topicId = newTopic.getId();

        logger.info("Creating a new topic with ID " + topicId);
        Topic addedTopic = topicService.add(newTopic);

        logger.info("Topic ID:" + addedTopic.getId() + " added.");
    }

    @PutMapping("/api/topics")
    public void putHandler(@RequestBody Topic updatedTopic) {
        var topicId = updatedTopic.getId();

        // Asking the service to update the topic
        logger.info("Updating topic ID:" + topicId);
        topicService.updateTopic(updatedTopic);

        logger.info("Topic ID:" + topicId + " updated");
    }

    @DeleteMapping("/api/topics/{topicID}")
    public void deleteHandler(@PathVariable Integer topicID) {
        logger.info("Deleting Topic with ID:" + topicID);
        topicService.deleteTopic(topicID);
    }
}
