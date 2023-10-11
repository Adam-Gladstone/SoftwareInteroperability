namespace StatisticsViewerWinUI.Model
{
    public class ResultStatistic
    {
        public ResultStatistic(string name, double value)
        {
            Name = name;
            Value = value;
        }
    
        public string Name { get; set; }
        public double Value { get; set; }
    }
}
