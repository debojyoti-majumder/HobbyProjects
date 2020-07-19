package org.gitbub.debojyoti.CourseDemoApp.topic;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
public class TopicController {

    @Autowired
    private TopicService topicService;

    @RequestMapping("/getalltopics")
    public List<Topic> getAllTopics() {
        return topicService.getAllTopics();
    }
}
