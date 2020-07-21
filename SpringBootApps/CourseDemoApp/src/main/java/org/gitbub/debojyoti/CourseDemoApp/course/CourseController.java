package org.gitbub.debojyoti.CourseDemoApp.course;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;

@Controller
public class CourseController {
    private static final Logger logger = LoggerFactory.getLogger(CourseController.class);

    @PostMapping("/api/topics/{topicId}/course")
    public void addNewCourse(@PathVariable String topicId, @RequestBody Course newCourse) {
        logger.info("Trying to add new course to topic Id" + topicId);
    }
}
