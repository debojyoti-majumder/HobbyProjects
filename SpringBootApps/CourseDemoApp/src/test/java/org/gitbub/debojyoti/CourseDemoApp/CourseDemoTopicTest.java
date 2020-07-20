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
    public void getTopicsBasicTest() {
        String resourceUri = "http://localhost:" + port + "/api/topics";
        List topics = restTemplate.getForObject(resourceUri, List.class);
        assertThat(topics.size() != 0 );
    }
}
