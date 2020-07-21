package org.gitbub.debojyoti.CourseDemoApp.topic;

import org.gitbub.debojyoti.CourseDemoApp.course.Course;

import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.OneToMany;

import java.util.ArrayList;
import java.util.List;

@Entity
public class Topic {
    @Id
    private String id;
    private String caption;
    private String description;

    @OneToMany
    private List<Course> courses;

    public Topic() {
        courses = new ArrayList<>();
    }

    public Topic(String id, String caption, String description) {
        this.id = id;
        this.caption = caption;
        this.description = description;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getCaption() {
        return caption;
    }

    public void setCaption(String caption) {
        this.caption = caption;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    // As of now let this always true, but would be changed later
    public boolean addCourse(Course newCourse) {
        courses.add(newCourse);
        return true;
    }
}
