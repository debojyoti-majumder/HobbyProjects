package org.gitbub.debojyoti.CourseDemoApp.topic;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
public class TopicController {

    @Autowired
    private TopicService topicService;

    // By default it is a mapping for a get request
    @RequestMapping("/topics")
    public List<Topic> getAllTopics() {
        return topicService.getAllTopics();
    }

    @RequestMapping("/topic/{topicID}")
    public Topic getTopicWithId(@PathVariable("topicID") String id) {
        // As the return type of the service is Optional may be there is check required to report error
        // TODO: Add Error handling if optional value is null
        return topicService.getTopic(id).get();
    }
}
