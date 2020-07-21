package org.gitbub.debojyoti.CourseDemoApp;
import org.gitbub.debojyoti.CourseDemoApp.topic.Topic;
import org.gitbub.debojyoti.CourseDemoApp.topic.TopicController;

import org.junit.jupiter.api.Test;
import static org.assertj.core.api.Assertions.assertThat;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.web.client.TestRestTemplate;
import org.springframework.boot.web.server.LocalServerPort;

import java.util.List;

@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
public class CourseDemoTopicTest {
    @Autowired
    private TopicController topicController;

    @LocalServerPort
    private int port;

    @Autowired
    private TestRestTemplate restTemplate;

    @Test
    public void contextLoads() {
        assertThat(topicController).isNotNull();
    }

    @Test
    public void addNewTopic() {
        Topic tp = new Topic();

        // Setting up the object
        tp.setDescription("This is simple description");
        tp.setCaption("Simple");

        // First we add the topic and then check if it is actually present or not
        String resourceUri = "http://localhost:" + port + "/api/topics";
        Topic addedTopic = restTemplate.postForObject(resourceUri, tp, Topic.class);
        List<Topic> topics = restTemplate.getForObject(resourceUri, List.class);

        // This test if the topic have been added or not
        assertThat(topics.contains(addedTopic));
    }

    @Test
    public void getTopicsBasicTest() {
        String resourceUri = "http://localhost:" + port + "/api/topics";
        List<Topic> topics = restTemplate.getForObject(resourceUri, List.class);

        assertThat(topics).isNotNull();
    }
}
