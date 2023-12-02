using System;
using System.IO;
using System.Linq;
using System.Collections.Generic;

namespace day8
{
    class Mapping
    {
        private Dictionary<string, int> mapping;

        public Mapping(string[] patterns)
        {
            /*  Reference for the Segments:
             *
             *  0:      1:      2:      3:      4:
             *   aaaa    ....    aaaa    aaaa    ....
             *  b    c  .    c  .    c  .    c  b    c
             *  b    c  .    c  .    c  .    c  b    c
             *   ....    ....    dddd    dddd    dddd
             *  e    f  .    f  e    .  .    f  .    f
             *  e    f  .    f  e    .  .    f  .    f
             *   gggg    ....    gggg    gggg    ....
             *
             * 5:      6:      7:      8:      9:
             *  aaaa    aaaa    aaaa    aaaa    aaaa
             * b    .  b    .  .    c  b    c  b    c
             * b    .  b    .  .    c  b    c  b    c
             *  dddd    dddd    ....    dddd    dddd
             * .    f  e    f  .    f  e    f  .    f
             * .    f  e    f  .    f  e    f  .    f
             *  gggg    gggg    ....    gggg    gggg
             */
            var one = new HashSet<char>(patterns.First(s => s.Length == 2));
            var seven = new HashSet<char>(patterns.First(s => s.Length == 3));
            var four = new HashSet<char>(patterns.First(s => s.Length == 4));
            var eight = new HashSet<char>(patterns.First(s => s.Length == 7));

            // transform each element to HashSet, since we want to do Set Operations
            var ps = patterns.Select(p => new HashSet<char>(p));
            // "6" has 6 segments and doesn't have c Segment
            var six = ps.First(p => p.Count == 6 && !one.IsProperSubsetOf(p));
            // "9" has 6 segments and has d segment
            var nine = ps.First(p => p.Count == 6 && four.IsProperSubsetOf(p));
            // "0" has 6 segments and doesn't have d segment
            var bd = new HashSet<char>(four.Except(one));
            var zero = ps.First(p => p.Count == 6 && !bd.IsProperSubsetOf(p));
            
            var aeg = new HashSet<char>(eight.Except(four));
            // "2" has 5 segments and has all of a,e and g
            var two = ps.First(p => p.Count == 5 && aeg.IsProperSubsetOf(p));
            // "5" has 5 segments and has b
            var five = ps.First(p => p.Count == 5 && bd.IsProperSubsetOf(p));
            var e = new HashSet<char>(eight.Except(nine));
            var three = new HashSet<char>(two.Except(e).Union(one));
            
            mapping = new Dictionary<string, int>();
            mapping.Add(ToSortedString(zero), 0);
            //Console.WriteLine($"0: {ToSortedString(zero)}");
            mapping.Add(ToSortedString(one), 1);
            //Console.WriteLine($"1: {ToSortedString(one)}");
            mapping.Add(ToSortedString(two), 2);
            //Console.WriteLine($"2: {ToSortedString(two)}");
            mapping.Add(ToSortedString(three), 3);
            //Console.WriteLine($"3: {ToSortedString(three)}");
            mapping.Add(ToSortedString(four), 4);
            //Console.WriteLine($"4: {ToSortedString(four)}");
            mapping.Add(ToSortedString(five), 5);
            //Console.WriteLine($"5: {ToSortedString(five)}");
            mapping.Add(ToSortedString(six), 6);
            //Console.WriteLine($"6: {ToSortedString(six)}");
            mapping.Add(ToSortedString(seven), 7);
            //Console.WriteLine($"7: {ToSortedString(seven)}");
            mapping.Add(ToSortedString(eight), 8);
            //Console.WriteLine($"8: {ToSortedString(eight)}");
            mapping.Add(ToSortedString(nine), 9);
            //Console.WriteLine($"9: {ToSortedString(nine)}");

        }
        public int ClassifyDigit(string digit)
        {
            return mapping[ToSortedString(new HashSet<char>(digit))];
        }

        public static string ToSortedString(HashSet<char> d)
        {
            var chrs = d.ToArray();
            Array.Sort(chrs);
            return new string(chrs);
        }

    }
    class Program
    {
        static void Main(string[] args)
        {
            var lines = File.ReadLines("input.txt");
            Console.WriteLine($"Task1: {Task1(lines)}");
            Console.WriteLine($"Task2: {Task2(lines)}");
        }

        static bool is_unique(string digit)
        {
            return digit.Length == 2 // "1"
            || digit.Length == 4 // "4"
            || digit.Length == 3 // "7"
            || digit.Length == 7; // "8"
        }

        static int Task1(IEnumerable<string> lines) {
            int count = 0;
            foreach (string line in lines)
            {
                var split = line.Split('|');
                var output_digits = split[1].Trim().Split(' ');
                foreach (string digit in output_digits)
                {
                    if (is_unique(digit))
                    {
                        count++;
                    }
                }
            }
            return count;
        }

        static int Task2(IEnumerable<string> lines)
        {
            int sum = 0;
            foreach (string line in lines)
            {
                var split = line.Split('|');
                var patterns = split[0];
                var pattern_digits = patterns.Trim().Split(' ');
                var output_digits = split[1].Trim().Split(' ');

                var mapping = new Mapping(pattern_digits);

                int display_digit = 0;
                foreach (string digit in output_digits)
                {
                    display_digit *= 10;
                    display_digit += mapping.ClassifyDigit(digit);
                }

                sum += display_digit;
            }

            return sum;
        }
    }
}
