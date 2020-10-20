using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.Extensions.Configuration;

namespace Tutorial1.Pages.QuestionGroups
{
    public class ListViewModel : PageModel
    {
        public ListViewModel(IConfiguration configuration)
        {
            AppConfig = configuration;
        }

        public string WelcomeMessage { get; set; }
        private readonly IConfiguration AppConfig;

        public void OnGet()
        {
            WelcomeMessage = AppConfig["TopicsMessage"];
        }
    }
}