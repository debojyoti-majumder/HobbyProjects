package org.gitbub.debojyoti.CourseDemoApp.course;

import org.gitbub.debojyoti.CourseDemoApp.topic.Topic;
import org.gitbub.debojyoti.CourseDemoApp.topic.TopicRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;

@Controller
public class CourseController {
    private static final Logger logger = LoggerFactory.getLogger(CourseController.class);

    @Autowired
    private TopicRepository repository;

    @PostMapping("/api/topics/{topicId}/course")
    public void addNewCourse(@PathVariable String topicId, @RequestBody Course newCourse) {
        logger.info("Trying to add new course to topic Id:" + topicId);
        var parentTopic = repository.findById(topicId);

        if (parentTopic.isEmpty()) return;

        // Obtain the parent topic
        Topic pTopic = parentTopic.get();
        logger.info("Got parent topic with name" + pTopic.getCaption());

        // TODO: This creates a crash, saying there are no repository, has to be fixed
        pTopic.addCourse(newCourse);
        repository.save(pTopic);
    }
}
