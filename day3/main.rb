require 'fileutils'

def get_histogram(input)
  zeros = Array.new(12, 0)
  ones = Array.new(12, 0)

  input.each{ |line|
    line.each_char.with_index { |c, i|
      if c == "0" then
        zeros[i] += 1
      elsif c == "1" then
        ones[i] += 1
      end
    }
  }
  return zeros, ones
end

input = File.readlines("input.txt").map(&:chomp)

zeros, ones = get_histogram(input)

gamma = ""
epsilon = ""

for i in 0..11 do
  x = zeros[i]
  y = ones[i]
  if y > x then
    gamma += "1"
    epsilon += "0"
  else
    gamma += "0"
    epsilon += "1"
  end
end

puts "Task1: #{gamma.to_i(2) * epsilon.to_i(2)}"


input = File.readlines("input.txt")
position = 0
# oxygen
while input.size > 1 do
  zeros, ones = get_histogram(input)
  if ones[position] >= zeros[position] then
    keep = "1"
  else
    keep = "0"
  end
  input.keep_if { |x| x[position] == keep }
  position += 1
end
oxygen = input[0].to_i(2)

input = File.readlines("input.txt")
position2 = 0
# CO2
while input.size > 1 do
  zeros, ones = get_histogram(input)
  if ones[position2] < zeros[position2] then
    keep = "1"
  else
    keep = "0"
  end
  input.keep_if { |x| x[position2] == keep }
  position2 += 1
end
co2 = input[0].to_i(2)


puts "Task2: #{oxygen * co2}"
