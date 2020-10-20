using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Tutorial1.Core;

namespace Tutorial1.Data
{
    public interface ITopicData
    {
        IEnumerable<Topic> GetByName(string name = null);
    }

    public class InMemoryTopicData : ITopicData
    {
        readonly List<Topic> topics;

        public InMemoryTopicData()
        {
            topics = new List<Topic>()
            {
                new Topic(1, "First Topic", "This is a place holder"),
                new Topic(2, "C++", "This is a place holder"),
                new Topic(3, "Go Lang", "This is a place holder"),
                new Topic(4, "Rust", "This is a place holder"),
            };
        }

        public IEnumerable<Topic> GetByName(string name = null)
        {
            return from t in topics
                   where string.IsNullOrEmpty(name) || t.Caption.StartsWith(name)
                   orderby t.Caption
                   select t;
        }
    }
}
