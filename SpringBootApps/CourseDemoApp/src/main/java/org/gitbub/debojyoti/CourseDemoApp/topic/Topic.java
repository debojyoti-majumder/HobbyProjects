package org.gitbub.debojyoti.CourseDemoApp.topic;

import javax.persistence.Entity;
import javax.persistence.Id;

@Entity
public class Topic {
    @Id
    public String id;
    public String caption;
    public String description;

    public Topic() {

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
}
