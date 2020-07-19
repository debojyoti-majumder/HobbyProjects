package org.gitbub.debojyoti.CourseDemoApp;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class CourseDemoAppApplication {
	private static final Logger logger = LoggerFactory.getLogger(CourseDemoAppApplication.class);

	public static void main(String[] args) {
		logger.info("Starting Course Demo Application");
		SpringApplication.run(CourseDemoAppApplication.class, args);
	}

}
