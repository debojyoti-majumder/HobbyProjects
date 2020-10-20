using System;
using System.Collections.Generic;
using System.Text;

namespace Tutorial1.Core
{
    class Topic
    {
        public int Id { get; }
        public string Caption { get; }
        public string Description { get; }
        public List<Question> Questions { get; }

        public Topic(int id, string caption, string desc)
        {
            Id = id;
            Caption = caption;
            Description = desc;
            Questions = new List<Question>();
        }

        public void AddQuestion(Question q)
        {
            Questions.Add(q);
        }
    }
}
