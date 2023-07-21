#ifndef SORT_H
#define SORT_H

#include "Tracker.h"
#include "Hungarian.h"
#include "SortRect.h"

#include <vector>
#include <set>
#include <stdio.h>
#include <string.h>



typedef struct Point_struct{
    double x;
    double y;
}Point_struct;

typedef struct Line_struct{
    Point_struct p1;
    Point_struct p2;
}Line_struct;

class Sort {
public:
  Sort(int maxAge, int minHits, float iouThreshold);

  std::vector<SortRect> update(std::vector<SortRect> rects);


  long long dist(const Point_struct* p1, const Point_struct* p2);
  int ccw(const Point_struct* p1, const Point_struct* p2, const Point_struct* p3);
  int SortComparator(const Point_struct* left, const Point_struct* right);
  void QuickSort(Point_struct* a, int lo, int hi);
  int LineComparator(Point_struct left, Point_struct right);
  void swap(Point_struct* p1, Point_struct* p2);
  int LineIntersection(Line_struct l1, Line_struct l2);
  int PolygonInOut(Point_struct p, int num_vertex, Point_struct* vertices);
  Point_struct IntersectionPoint_struct(const Point_struct* p1, const Point_struct* p2, const Point_struct* p3, const Point_struct* p4);
  double GetPolygonArea(int num_points, Point_struct* points);
  double GetIntersection(int num1, Point_struct* points1, int num2, Point_struct* points2);
  double GetIoU(int num1, Point_struct* points1, int num2, Point_struct* points2);

  Point_struct p;
  int interection_num;
  Point_struct intersection_point[10];



private:
  float iou(SortRect rect1, SortRect rect2);

  HungarianAlgorithm HungAlgo;

  int maxAge;
  int minHits;
  float iouThreshold;

  std::vector<Tracker> trackers;
};

#endif