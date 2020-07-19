package org.gitbub.debojyoti.CourseDemoApp.topic;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

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
        // As the return type of the service is Optional may be there is check required to report error
        // TODO: Add Error handling if optional value is null
        logger.info("Getting topic with Topic ID" + id);
        return topicService.getTopic(id).get();
    }

    @PostMapping(value = "/topics")
    public void postTopic(@RequestBody Topic newTopic) {
        // TODO: Same as the other GET there is no error handling that have been implemented
        logger.info("Creating a new topic with ID" + newTopic.getId());
        topicService.add(newTopic);

        return;
    }
}
