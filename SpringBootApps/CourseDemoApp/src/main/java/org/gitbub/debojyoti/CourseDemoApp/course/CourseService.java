package org.gitbub.debojyoti.CourseDemoApp.course;

import org.gitbub.debojyoti.CourseDemoApp.topic.Topic;
import org.gitbub.debojyoti.CourseDemoApp.topic.TopicRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;

@Service
public class CourseService {

    @Autowired
    private TopicRepository topicRepository;

    @Autowired
    private CourseRepository courseRepository;

    public Course addCourse(@PathVariable Integer topicId, @RequestBody Course newCourse)
    {
        var returnedResult = topicRepository.findById(topicId);
        if( returnedResult.isEmpty() ) return null;

        // Getting the topic which needs to be updated
        Topic parentTopic = returnedResult.get();

        // Saving the course first
        Course savedItem = courseRepository.save(newCourse);
        if( savedItem == null ) return null;

        // Update the topic repository
        parentTopic.addCourse(savedItem);
        topicRepository.save(parentTopic);

        return savedItem;
    }
}
