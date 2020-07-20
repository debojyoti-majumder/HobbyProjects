package org.gitbub.debojyoti.CourseDemoApp.topic;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;

import org.springframework.http.HttpStatus;
import org.springframework.web.server.ResponseStatusException;


import java.util.List;

@RestController
public class TopicController {

    @Autowired
    private TopicService topicService;
    private static final Logger logger = LoggerFactory.getLogger(TopicController.class);

    // By default it is a mapping for a get request
    @GetMapping("/topics")
    public List<Topic> getAllTopics() {
        logger.info("Listing all the topics");
        return topicService.getAllTopics();
    }

    @GetMapping("/topic/{topicID}")
    public Topic getTopicWithId(@PathVariable("topicID") String id) {
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

    @PostMapping(value = "/topics")
    public void postTopic(@RequestBody Topic newTopic) {
        logger.info("Creating a new topic with ID " + newTopic.getId());
        boolean isAdded = topicService.add(newTopic);

        // The repository might not be able to add the new topic
        if(!isAdded) {
            var errorMessage = "A topic with ID "+ newTopic.getId() + " is already present";
            logger.warn(errorMessage);
            throw new ResponseStatusException(HttpStatus.CONFLICT, errorMessage);
        }
    }
}
