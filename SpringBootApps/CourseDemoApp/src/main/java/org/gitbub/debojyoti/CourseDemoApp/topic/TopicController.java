package org.gitbub.debojyoti.CourseDemoApp.topic;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.web.bind.annotation.*;

import org.springframework.http.HttpStatus;
import org.springframework.web.server.ResponseStatusException;


import java.util.List;

@RestController
@RequestMapping("/api/topics")
public class TopicController {

    @Autowired
    private TopicService topicService;
    private static final Logger logger = LoggerFactory.getLogger(TopicController.class);

    // By default it is a mapping for a get request
    @GetMapping
    public List<Topic> getAllTopics() {
        logger.info("Listing all the topics");
        return topicService.getAllTopics();
    }

    @GetMapping("/{topicID}")
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

    @PostMapping
    public void postTopic(@RequestBody Topic newTopic) {
        var topicId = newTopic.getId();

        logger.info("Creating a new topic with ID " + topicId);
        boolean isAdded = topicService.add(newTopic);

        // The repository might not be able to add the new topic
        if(!isAdded) {
            var errorMessage = "A topic with ID "+ topicId + " is already present";
            logger.warn(errorMessage);
            throw new ResponseStatusException(HttpStatus.CONFLICT, errorMessage);
        }

        logger.info("Topic ID:" + topicId + " added.");
    }

    @PutMapping
    public void putHandler(@RequestBody Topic updatedTopic) {
        var topicId = updatedTopic.getId();

        // Asking the service to update the topic
        logger.info("Updating topic ID:" + topicId);
        boolean isUpdated = topicService.updateTopic(updatedTopic);

        // As of now the only reason topic might not be updated is the topic id is
        // not found
        if ( false == isUpdated ) {
            var errorMessage = "No found topic with ID:"+ topicId;
            logger.warn(errorMessage);
            throw new ResponseStatusException(HttpStatus.NOT_MODIFIED, errorMessage);
        }

        logger.info("Topic ID:" + topicId + " updated");
    }
}
