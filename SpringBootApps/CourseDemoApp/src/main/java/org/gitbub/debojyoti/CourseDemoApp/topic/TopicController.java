package org.gitbub.debojyoti.CourseDemoApp.topic;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Arrays;
import java.util.List;

@RestController
public class TopicController {

    @RequestMapping("/getalltopics")
    public List<Topic> getAllTopics() {
        return Arrays.asList(
                new Topic("1", "Machine Learning", "Has a path for machine learning items"),
                new Topic("2,", "Windows System Programming", "Windows kernel programming and stuff")
        );
    }
}
