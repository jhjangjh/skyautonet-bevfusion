#include "Sort.h"

#include <cfloat>

Sort::Sort(int maxAge = 2, int minHits = 3, float iouThreshold = 0.3) {
  this->maxAge = maxAge;
  this->minHits = minHits;
  this->iouThreshold = iouThreshold;
}

std::vector<SortRect> Sort::update(std::vector<SortRect> detections) {

    std::cout << "maxAge = " << maxAge << std::endl;
    std::cout << "minHits = " << minHits << std::endl;
    std::cout << "iouThres = " << iouThreshold << std::endl;



  if (trackers.size() == 0) {
    for (std::vector<SortRect>::size_type i = 0; i < detections.size(); i++) {
      TrackerState state = detections[i].toTrackerState();
      Tracker tracker = Tracker(state);

      trackers.push_back(tracker);
    }

    return std::vector<SortRect>();
  }




  std::vector<SortRect> predictions;
  for (std::vector<SortRect>::size_type i = 0; i < trackers.size(); i++) {
    TrackerState state = trackers[i].predict();

    SortRect rect;
    rect.fromTrackerState(state);
    rect.id = 0;
    predictions.push_back(rect);
  }
  


  vector<vector<double>> iouMatrix;
  iouMatrix.resize(predictions.size(), vector<double>(detections.size(), 0));

  for (std::vector<SortRect>::size_type i = 0; i < predictions.size(); i++)
    for (std::vector<SortRect>::size_type j = 0; j < detections.size(); j++){
        // if(iou(predictions[i], detections[j]) != 0)
        // {
        //     std::cout << "iou : " << iou(predictions[i], detections[j]) << std::endl;
        // } 
      iouMatrix[i][j] = 1 - iou(predictions[i], detections[j]);
    }

  vector<int> assignment; 


  HungAlgo.Solve(iouMatrix, assignment);


  set<int> allItems;
  set<int> matchedItems;
  set<int> unmatchedDetections;

  for (std::vector<SortRect>::size_type i = 0; i < detections.size(); i++) allItems.insert(i);

  for (std::vector<SortRect>::size_type i = 0; i < predictions.size(); i++)
    if (assignment[i] != -1) matchedItems.insert(assignment[i]);

  std::set_difference(allItems.begin(), allItems.end(), matchedItems.begin(),
                      matchedItems.end(),
                      insert_iterator<set<int>>(unmatchedDetections,
                                                unmatchedDetections.begin()));

  vector<std::pair<int, int>> matchedPairs;
  for (std::vector<SortRect>::size_type i = 0; i < assignment.size(); i++) {
    if (assignment[i] == -1) continue;

    if (1 - iouMatrix[i][assignment[i]] < iouThreshold)
      unmatchedDetections.insert(assignment[i]);
    else
      matchedPairs.push_back(make_pair(i, assignment[i]));
  }

  for (auto pair : matchedPairs) {
    int trackerIndex = pair.first;
    int detectionIndex = pair.second;

    TrackerState state = detections[detectionIndex].toTrackerState();

    trackers[trackerIndex].update(state);
  }

  for (auto detectionIndex : unmatchedDetections) {
    TrackerState state = detections[detectionIndex].toTrackerState();

    Tracker tracker = Tracker(state);
    trackers.push_back(tracker);
  }

  std::vector<SortRect> result;
  for (auto it = trackers.begin(); it != trackers.end();) {
    if ((*it).m_time_since_update > maxAge) {
      it = trackers.erase(it);
    } else {
      if ((*it).m_time_since_update < 1 && (*it).m_hit_streak >= minHits) {
        TrackerState state = (*it).getState();

        SortRect rect;
        rect.fromTrackerState(state);
        rect.id = int((*it).m_id);
        // std:: cout << rect.id << std::endl;
        result.push_back(rect);
      }

      it++;
    }
  }

  return result;
}

float Sort::iou(SortRect rect1, SortRect rect2) {

    // interection_num = 0;

    // // SortRect -> Point_struct

    // //  p0-----p1
    // //  |       |
    // //  |   .   |
    // //  |       |
    // //  p2-----p3

    // // 원점기준 각 점의 좌표

    // float rect1_O_x0 = -rect1.width / 2.0;
    // float rect1_O_x1 =  rect1.width / 2.0;
    // float rect1_O_x2 = -rect1.width / 2.0;
    // float rect1_O_x3 =  rect1.width / 2.0;
    // float rect1_O_y0 =  rect1.length / 2.0;
    // float rect1_O_y1 =  rect1.length / 2.0;
    // float rect1_O_y2 = -rect1.length / 2.0;
    // float rect1_O_y3 = -rect1.length / 2.0;

    // float rect2_O_x0 = -rect2.width / 2.0;
    // float rect2_O_x1 =  rect2.width / 2.0;
    // float rect2_O_x2 = -rect2.width / 2.0;
    // float rect2_O_x3 =  rect2.width / 2.0;
    // float rect2_O_y0 =  rect2.length / 2.0;
    // float rect2_O_y1 =  rect2.length / 2.0;
    // float rect2_O_y2 = -rect2.length / 2.0;
    // float rect2_O_y3 = -rect2.length / 2.0;

    // // 원점에서 회전변환된 각 점의 좌표

    // float theta1 = rect1.yaw - M_PI / 2;
    // float theta2 = rect2.yaw - M_PI / 2;

    // float rect1_rotated_O_x0 = rect1_O_x0 * std::cos(theta1) - rect1_O_y0 * std::sin(theta1);
    // float rect1_rotated_O_x1 = rect1_O_x1 * std::cos(theta1) - rect1_O_y1 * std::sin(theta1);
    // float rect1_rotated_O_x2 = rect1_O_x2 * std::cos(theta1) - rect1_O_y2 * std::sin(theta1);
    // float rect1_rotated_O_x3 = rect1_O_x3 * std::cos(theta1) - rect1_O_y3 * std::sin(theta1);
    // float rect1_rotated_O_y0 = rect1_O_x0 * std::sin(theta1) + rect1_O_y0 * std::cos(theta1);
    // float rect1_rotated_O_y1 = rect1_O_x1 * std::sin(theta1) + rect1_O_y1 * std::cos(theta1);
    // float rect1_rotated_O_y2 = rect1_O_x2 * std::sin(theta1) + rect1_O_y2 * std::cos(theta1);
    // float rect1_rotated_O_y3 = rect1_O_x3 * std::sin(theta1) + rect1_O_y3 * std::cos(theta1);

    // float rect2_rotated_O_x0 = rect2_O_x0 * std::cos(theta2) - rect2_O_y0 * std::sin(theta2);
    // float rect2_rotated_O_x1 = rect2_O_x1 * std::cos(theta2) - rect2_O_y1 * std::sin(theta2);
    // float rect2_rotated_O_x2 = rect2_O_x2 * std::cos(theta2) - rect2_O_y2 * std::sin(theta2);
    // float rect2_rotated_O_x3 = rect2_O_x3 * std::cos(theta2) - rect2_O_y3 * std::sin(theta2);
    // float rect2_rotated_O_y0 = rect2_O_x0 * std::sin(theta2) + rect2_O_y0 * std::cos(theta2);
    // float rect2_rotated_O_y1 = rect2_O_x1 * std::sin(theta2) + rect2_O_y1 * std::cos(theta2);
    // float rect2_rotated_O_y2 = rect2_O_x2 * std::sin(theta2) + rect2_O_y2 * std::cos(theta2);
    // float rect2_rotated_O_y3 = rect2_O_x3 * std::sin(theta2) + rect2_O_y3 * std::cos(theta2);

    // // 원점에서 회전변환 시킨 각 점의 좌표를 각 박스의 중심으로 평행이동

    // float rect1_rotated_x0 = rect1_rotated_O_x0 + rect1.centerX; 
    // float rect1_rotated_x1 = rect1_rotated_O_x1 + rect1.centerX;
    // float rect1_rotated_x2 = rect1_rotated_O_x2 + rect1.centerX;
    // float rect1_rotated_x3 = rect1_rotated_O_x3 + rect1.centerX;
    // float rect1_rotated_y0 = rect1_rotated_O_y0 + rect1.centerY;
    // float rect1_rotated_y1 = rect1_rotated_O_y1 + rect1.centerY;
    // float rect1_rotated_y2 = rect1_rotated_O_y2 + rect1.centerY;
    // float rect1_rotated_y3 = rect1_rotated_O_y3 + rect1.centerY;

    // float rect2_rotated_x0 = rect2_rotated_O_x0 + rect2.centerX;
    // float rect2_rotated_x1 = rect2_rotated_O_x1 + rect2.centerX;
    // float rect2_rotated_x2 = rect2_rotated_O_x2 + rect2.centerX;
    // float rect2_rotated_x3 = rect2_rotated_O_x3 + rect2.centerX;
    // float rect2_rotated_y0 = rect2_rotated_O_y0 + rect2.centerY;
    // float rect2_rotated_y1 = rect2_rotated_O_y1 + rect2.centerY;
    // float rect2_rotated_y2 = rect2_rotated_O_y2 + rect2.centerY;
    // float rect2_rotated_y3 = rect2_rotated_O_y3 + rect2.centerY;

    // Point_struct points1[10];
    // Point_struct points2[10];

    // points1[0].x = rect1_rotated_x0;   points1[0].y = rect1_rotated_y0;
    // points1[1].x = rect1_rotated_x1;   points1[1].y = rect1_rotated_y1;
    // points1[2].x = rect1_rotated_x2;   points1[2].y = rect1_rotated_y2;
    // points1[3].x = rect1_rotated_x3;   points1[3].y = rect1_rotated_y3;

    // points2[0].x = rect2_rotated_x0;   points2[0].y = rect2_rotated_y0;
    // points2[1].x = rect2_rotated_x1;   points2[1].y = rect2_rotated_y1;
    // points2[2].x = rect2_rotated_x2;   points2[2].y = rect2_rotated_y2;
    // points2[3].x = rect2_rotated_x3;   points2[3].y = rect2_rotated_y3;

    // float iou = Sort::GetIoU(4, points1, 4, points2);
    
  float rect1_x1 = rect1.centerX - rect1.width / 2.0;
  float rect1_y1 = rect1.centerY - rect1.length / 2.0;
  float rect1_x2 = rect1.centerX + rect1.width / 2.0;
  float rect1_y2 = rect1.centerY + rect1.length / 2.0;

  float rect2_x1 = rect2.centerX - rect2.width / 2.0;
  float rect2_y1 = rect2.centerY - rect2.length / 2.0;
  float rect2_x2 = rect2.centerX + rect2.width / 2.0;
  float rect2_y2 = rect2.centerY + rect2.length / 2.0;

  float x1 = max(rect1_x1, rect2_x1);
  float y1 = max(rect1_y1, rect2_y1);
  float x2 = min(rect1_x2, rect2_x2);
  float y2 = min(rect1_y2, rect2_y2);

  float w = max(0.f, x2 - x1);
  float h = max(0.f, y2 - y1);

  float area1 = (rect1_x2 - rect1_x1) * (rect1_y2 - rect1_y1);
  float area2 = (rect2_x2 - rect2_x1) * (rect2_y2 - rect2_y1);
  float area3 = w * h;

  float iou = area3 / (area1 + area2 - area3 + DBL_EPSILON);


  return iou;
}

long long Sort::dist(const Point_struct* p1, const Point_struct* p2){
    return (long long)(p1->x - p2->x)*(p1->x - p2->x) + (long long)(p1->y - p2->y)*(p1->y - p2->y);
}

int Sort::ccw(const Point_struct* p1, const Point_struct* p2, const Point_struct* p3){

    int cross_product = (p2->x - p1->x)*(p3->y - p1->y) - (p3->x - p1->x)*(p2->y - p1->y);

    if (cross_product > 0){
        return 1;
    }
    else if (cross_product < 0){
        return -1;
    }
    else{
        return 0;
    }
}

// right가 left의 반시계 방향에 있으면 true이다.
// true if right is counterclockwise to left.
// Point_struct p;
int Sort::SortComparator(const Point_struct* left, const Point_struct* right){
    int ret;
    int direction = Sort::ccw(&p, left, right);
    if(direction == 0){
        ret = (Sort::dist(&p, left) < Sort::dist(&p, right));
    }
    else if(direction == 1){
        ret = 1;
    }
    else{
        ret = 0;
    }
    return ret;
}

void Sort::QuickSort(Point_struct* a, int lo, int hi){
    if(hi - lo <= 0){
        return;
    }

    // 현재 배열 범위의 중앙값을 피벗으로 선택한다.
    // Select the median as pivot in the current array range.
    Point_struct pivot = a[lo + (hi-lo+1)/2];
    int i = lo, j = hi;

    // 정복 과정
    // Conquer process
    while(i <= j){
        // 피벗의 왼쪽에는 comparator(타겟, "피벗")을 만족하지 않는 인덱스를 선택 (i)
        // On the left side of the pivot, select an index that doesn't satisfy the comparator(target, "pivot"). (i)
        while(Sort::SortComparator(&a[i], &pivot)) i++;
        
        // 피벗의 오른쪽에는 comparator("피벗", 타겟)을 만족하지 않는 인덱스를 선택 (j)
        // On the right side of the pivot, select an index that doesn't satisfy the comparator("pivot", target). (j)
        while(Sort::SortComparator(&pivot, &a[j])) j--;
        // (i > j) 피벗의 왼쪽에는 모든 값이 피벗보다 작고 피벗의 오른쪽에는 모든 값이 피벗보다 큰 상태가 되었음.
        // (i > j) On the left side of the pivot, all values are smaller than the pivot, and on the right side of the pivot, all values are larger than the pivot.
        if(i > j){
            break;
        }

        // i번째 값은 피벗 보다 크고 j번째 값은 피벗보다 작으므로 두 값을 스왑한다.
        // The i-th value is larger than the pivot and the j-th value is smaller than the pivot, so swap the two values.
        Point_struct temp = a[i];
        a[i] = a[j];
        a[j] = temp;

        // 인덱스 i를 1증가 시키고 인덱스 j를 1 감소 시켜서 탐색 범위를 안쪽으로 좁힌다.
        // Narrow the search inward by increasing index i by one and decreasing index j by one.
        i++;
        j--;
    }

    // 분할 과정
    // Divide process
    Sort::QuickSort(a, lo, j);
    Sort::QuickSort(a, i, hi);
}



// right가 left 보다 크면 true를 반환합니다.
// if right is greater than left, it is true
int Sort::LineComparator(Point_struct left, Point_struct right){
    int ret;
    if(left.x == right.x){
        ret = (left.y <= right.y);
    }
    else{
        ret = (left.x <= right.x);
    }
    return ret;
}

// 입력받은 Point_struct 구조체의 값을 교환합니다.
// Exchanges the value of the input Point_struct structure.
void Sort::swap(Point_struct* p1, Point_struct* p2){
    Point_struct temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// 두 선분이 교차하면 1을 교차하지 않으면 0을 반환합니다.
// If the two segments intersect, they will return 1 if they do not intersect 0.
int Sort::LineIntersection(Line_struct l1, Line_struct l2){
    int ret;
    // l1을 기준으로 l2가 교차하는 지 확인한다.
    // Check if l2 intersects based on l1.
    int l1_l2 = Sort::ccw(&l1.p1, &l1.p2, &l2.p1) * Sort::ccw(&l1.p1, &l1.p2, &l2.p2);
    // l2를 기준으로 l1이 교차하는 지 확인한다.
    // Check if l1 intersects based on l2.
    int l2_l1 = Sort::ccw(&l2.p1, &l2.p2, &l1.p1) * Sort::ccw(&l2.p1, &l2.p2, &l1.p2);

    ret = (l1_l2 < 0) && (l2_l1 < 0);

    return ret;
}

int Sort::PolygonInOut(Point_struct p, int num_vertex, Point_struct* vertices){

    int ret = 0;

    // 마지막 꼭지점과 첫번째 꼭지점이 연결되어 있지 않다면 오류를 반환한다.
    // If the last vertex and the first vertex are not connected, an error is returned.
    if (vertices[0].x != vertices[num_vertex].x || vertices[0].y != vertices[num_vertex].y){
        // printf("Last vertex and first vertex are not connected.");
        return -1;
    }

    for(int i = 0; i < num_vertex; ++i){
        
        // 점 p가 i번째 꼭지점과 i+1번째 꼭지점을 이은 선분 위에 있는 경우
        // If point p is on the line connecting the i and i + 1 vertices
        if( Sort::ccw(&vertices[i], &vertices[i+1], &p) == 0 ){
            int min_x = std::min(vertices[i].x, vertices[i+1].x);
            int max_x = std::max(vertices[i].x, vertices[i+1].x);
            int min_y = std::min(vertices[i].y, vertices[i+1].y);
            int max_y = std::max(vertices[i].y, vertices[i+1].y);

            // 점 p가 선분 내부의 범위에 있는 지 확인
            // Determine if point p is in range within line segment
            if(min_x <= p.x && p.x <= max_x && min_y <= p.y && p.y <= max_y){
                return 1;
            }
        }
        else{;}
    }

    // 다각형 외부에 임의의 점과 점 p를 연결한 선분을 만든다.
    // Create a line segment connecting a random point outside the polygon and point p.
    Point_struct outside_point;
    outside_point.x = 1; outside_point.y = 1234567;
    Line_struct l1;
    l1.p1 = outside_point;
    l1.p2 = p;

    // 앞에서 만든 선분과 다각형을 이루는 선분들이 교차되는 갯수가 센다.
    // Count the number of intersections between the previously created line segments and the polygonal segments.
    for(int i = 0; i < num_vertex; ++i){
        Line_struct l2;
        l2.p1 = vertices[i];
        l2.p2 = vertices[i+1];
        ret += Sort::LineIntersection(l1, l2);
    }

    // 교차한 갯수가 짝수인지 홀수인지 확인한다.
    // Check if the number of crossings is even or odd.
    ret = ret % 2;
    return ret;
}

// (p1, p2)를 이은 직선과 (p3, p4)를 이은 직선의 교차점을 구하는 함수
// Function to get intersection point with line connecting points (p1, p2) and another line (p3, p4).
Point_struct Sort::IntersectionPoint_struct(const Point_struct* p1, const Point_struct* p2, const Point_struct* p3, const Point_struct* p4){

    Point_struct ret;

    ret.x = ((p1->x*p2->y - p1->y*p2->x)*(p3->x - p4->x) - (p1->x - p2->x)*(p3->x*p4->y - p3->y*p4->x))/( (p1->x - p2->x)*(p3->y - p4->y) - (p1->y - p2->y)*(p3->x - p4->x) );

    ret.y = ((p1->x*p2->y - p1->y*p2->x)*(p3->y - p4->y) - (p1->y - p2->y)*(p3->x*p4->y - p3->y*p4->x)) / ( (p1->x - p2->x)*(p3->y - p4->y) - (p1->y - p2->y)*(p3->x - p4->x) );

    return ret;
}

// 다각형의 넓이를 구한다.
// find the area of a polygon
double Sort::GetPolygonArea(int num_points, Point_struct* points){
        double ret = 0;
        int i, j;
        i = num_points - 1;
        for(j = 0; j < num_points; ++j){
            ret += points[i].x * points[j].y - points[j].x * points[i].y;
            i = j;
        }
        ret = ret < 0 ? -ret : ret;
        ret /= 2;

        return ret;
}

// int interection_num;
// Point_struct intersection_point[10];
double Sort::GetIntersection(int num1, Point_struct* points1, int num2, Point_struct* points2){
    
    double ret;
    Line_struct l1, l2;

    // points1과 points2 각각을 반시계방향으로 정렬한다.
    // sort by counter clockwise point1 and points2.
    p = points1[0];
    Sort::QuickSort(points1, 1, num1-1);

    p = points2[0];
    Sort::QuickSort(points2, 1, num2-1);

    // 차례대로 점들을 이었을 때, 다각형이 만들어질 수 있도록 시작점을 마지막에 추가한다.
    // Add the starting point to the last in order to make polygon when connect points in order.
    points1[num1] = points1[0];
    points2[num2] = points2[0];

    // points1의 다각형 선분들과 points2의 다각형 선분들의 교차점을 구한다.
    // Find the intersection of the polygon segments of points1 and the polygon segments of points2.
    for(int i = 0; i < num1; ++i){
        l1.p1 = points1[i];
        l1.p2 = points1[i+1];
        for(int j = 0; j < num2; ++j){
            l2.p1 = points2[j];
            l2.p2 = points2[j+1];

            // 선분 l1과 l2가 교차한다면 교차점을 intersection_point에 저장한다.
            // If line segments l1 and l2 intersect, store the intersection at intersection_point.
            if(Sort::LineIntersection(l1, l2)){
                intersection_point[interection_num++] = 
                Sort::IntersectionPoint_struct(&l1.p1, &l1.p2, &l2.p1, &l2.p2);
            }
        }
    }

    for(int i = 0; i < num1; ++i){
        if(Sort::PolygonInOut(points1[i], num2, points2)){
            intersection_point[interection_num++] = points1[i];
        }
    }
    for(int i = 0; i < num2; ++i){
        if(Sort::PolygonInOut(points2[i], num1, points1)){
            intersection_point[interection_num++] = points2[i];
        }
    }
    
    // restore
    points1[num1].x = 0;    points1[num1].y = 0;
    points2[num2].x = 0;    points2[num2].y = 0;

    p = intersection_point[0];
    Sort::QuickSort(intersection_point, 1, interection_num-1);

    ret = Sort::GetPolygonArea(interection_num, intersection_point); 
    return ret;
}

double Sort::GetIoU(int num1, Point_struct* points1, int num2, Point_struct* points2){
    
    double ret;
    double A, B, union_area, intersection_area;
    memset(intersection_point, 0, sizeof(intersection_point));

    intersection_area = Sort::GetIntersection(num1, points1, num2, points2);
    A = Sort::GetPolygonArea(num1, points1);
    B = Sort::GetPolygonArea(num2, points2);
    union_area = A + B - intersection_area;

    ret = intersection_area / (union_area + DBL_EPSILON);       

    return ret;
}
