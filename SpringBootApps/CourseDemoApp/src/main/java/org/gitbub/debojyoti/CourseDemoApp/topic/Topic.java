package org.gitbub.debojyoti.CourseDemoApp.topic;

import com.fasterxml.jackson.annotation.JsonManagedReference;
import org.gitbub.debojyoti.CourseDemoApp.course.Course;

import javax.persistence.*;

import java.util.ArrayList;
import java.util.List;

@Entity
@Table(name = "topic")
public class Topic {
    @Id
    @GeneratedValue
    private Integer id;

    private String caption;
    private String description;

    @OneToMany
    private List<Course> courses;

    public Topic() {
        courses = new ArrayList<>();
    }

    public List<Course> getCourses() {
        return courses;
    }

    public void setCourses(List<Course> courses) {
        this.courses = courses;
    }

    public Topic(Integer id, String caption, String description) {
        this.id = id;
        this.caption = caption;
        this.description = description;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
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
