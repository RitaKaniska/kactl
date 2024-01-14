/**
 * Author: Anonymous
 * Date: Unknown
 * License: None
 * Description: Find the angle between 2 vectors
 */

typedef Point<double> P;

double angle(P &v, P &w){
    return acos(clamp(v.dot(w) / v.dist() / w.dist(), -1.0, 1.0)); 
}
