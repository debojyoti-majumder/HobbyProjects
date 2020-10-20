﻿using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.Extensions.Configuration;
using System.Collections.Generic;

using Tutorial1.Core;
using Tutorial1.Data;

namespace Tutorial1.Pages.QuestionGroups
{
    public class ListViewModel : PageModel
    {
        public string WelcomeMessage { get; set; }
        public IEnumerable<Topic> AllTopics { get; set; }

        // Depedency of the model
        private readonly IConfiguration appConfig;
        private readonly ITopicData topicData;

        public ListViewModel(IConfiguration configuration, ITopicData topicData)
        {
            appConfig = configuration;
            this.topicData = topicData;
        }

        public void OnGet(string searchTerm)
        {
            WelcomeMessage = appConfig["TopicsMessage"];
            AllTopics = topicData.GetByName(searchTerm);
        }
    }
}