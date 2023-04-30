require_relative "./pathfinder_ext"

module Pathfinder
  class Base
    attr_reader :size_x, :size_y, :start_x, :start_y, :end_x, :end_y, :forbidden

    def initialize(size_x, size_y, start_x, start_y, end_x, end_y, forbidden = [])
      @size_x = size_x
      @size_y = size_y
      @start_x = start_x
      @start_y = start_y
      @end_x = end_x
      @end_y = end_y
      @forbidden = forbidden
    end

    def call
      Pathfinder.findpath(size_x, size_y, start_x, start_y, end_x, end_y, forbidden)
    end

    def print_intro
      puts "field size: #{size_x}, #{size_y}"
      puts "start position: #{start_x}, #{start_y}"
      puts "end position: #{end_x}, #{end_y}"
      puts "\n"
    end

    def find_and_print_path
      print_intro
      path = self.call

      (size_y + 2).times do |cy|
        (size_x + 2).times do |cx|
          x = cx - 1
          y = cy - 1
          if cx == 0 || cy == 0 || x == size_x || y == size_y || forbidden.include?([x,y])
            print '##'
          elsif path.include?([x,y])
            print '::'
          else
            print '  '
          end
        end
        print "\n"
      end
      print "\n"
    end
  end
end
