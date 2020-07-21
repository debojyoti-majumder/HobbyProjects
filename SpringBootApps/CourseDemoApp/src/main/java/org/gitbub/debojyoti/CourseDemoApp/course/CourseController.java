package org.gitbub.debojyoti.CourseDemoApp.course;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.server.ResponseStatusException;

@Controller
public class CourseController {
    private static final Logger logger = LoggerFactory.getLogger(CourseController.class);

    @Autowired
    private CourseService service;

    @PostMapping("/api/topics/{topicId}/course")
    public Course addNewCourse(@PathVariable Integer topicId, @RequestBody Course newCourse) {
        logger.info("Trying to add new course to topic Id:" + topicId);
        var addedCourse = service.addCourse(topicId, newCourse);

        if( null == addedCourse ) {
            var errorMessage = "Was not able to add new course";
            logger.warn(errorMessage);
            throw new ResponseStatusException(HttpStatus.NOT_MODIFIED,errorMessage);
        }

        logger.info("Added new course");
        return addedCourse;
    }
}
