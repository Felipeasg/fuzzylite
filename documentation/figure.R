library('ggplot2')

isEq = function(a,b,error=1e-5){
    abs(a - b) <= error
}

isLt = function(a,b,error=1e-5){
    !isEq(a,b,error) & a < b
}

isGt = function(a,b,error=1e-5){
    !isEq(a,b,error) & a > b
}

isLE = function(a,b,error=1e-5){
    isEq(a,b,error) | a < b
}

isGE = function(a,b,error=1e-5){
    isEq(a,b,error) | a > b
}

#Scale: Scales a number to a different scale
Scale = function(value, toMin, toMax, fromMin=min(value), fromMax=max(value)){
      (toMax - toMin) / (fromMax - fromMin) * (value - fromMin) + toMin
}

#Basic

term.triangle = function(x, a, b, c){
    if (isLt(x,a) | isGt(x,c)) 
        0.0
    else if (isEq(x,b))
        1.0
    else if (isLt(x,b))
        (x - a) / (b - a)
    else 
        result = (c - x) / (c - b)    
}

term.trapezoid = function(x,a,b,c,d){
        if (isLt(x, a) | isGt(x, d))
            0.0
        else if (isLE(x, b))
            min(1.0, (x - a) / (b - a))
        else if (isLE(x, c))
            1.0
        else if (isLE(x, d))
            (d - x) / (d - c)
}

term.rectangle = function(x,a,b){
    if (isLt(x, a) | isGt(x,b)) 
        0.0
    else 1.0
}

term.discrete = function(x, a, b){
    diff = b-a
    if (isLt(x,a) | isGt(x,b))
        0.0
    else if (isLt(x,.25 * diff))
        Scale(x, 0, 1, a, a + diff*.25)
    else if (isLt(x, .5*diff))
        Scale(x,1,0.5, a + diff*.25, a + diff*.5)
    else if (isLt(x, .75*diff))
        Scale(x,0.5,1,a+diff*.5, a+diff*.75)
    else if (isLt(x, diff))
        Scale(x, 1, 0, a+diff*.75, a+diff)
    else {0.0}
#    else if (isLt(x, a*.5)
}


term.bell = function(x, center, width, slope){
    1.0 / (1.0 + abs((x - center) / width)**(2 * slope));
}

#EXTENDED

term.cosine = function(x, center, width){
    if (isLt(x, center-width/2.0) || isGt(x, center+width/2.0)){
        0.0
    }else{
        0.5 * (1.0 + cos(2.0 / width * pi * (x - center)))
    }
}

term.gaussian = function(x, mean, sd){
    exp((-(x - mean) * (x - mean)) / (2 * sd * sd));
}

term.gaussianProduct = function(x, meanA, sdA, meanB, sdB){
        xLEa = isLE(x, meanA)
        a = exp((-(x - meanA) * (x - meanA)) / (2 * sdA * sdA)) * xLEa + (1 - xLEa)
        xGEb = isGE(x, meanB)
        b = exp((-(x - meanB) * (x - meanB)) / (2 * sdB * sdB)) * xGEb + (1 - xGEb)
        a * b
}

term.bell = function(x, center, width, slope){
    1.0 / (1.0 + abs((x - center) / width)** (2 * slope))
}

term.piShape = function(x, bottomLeft, topLeft, topRight, bottomRight){
        a_b_ave = (bottomLeft + topLeft) / 2.0
        b_minus_a = topLeft - bottomLeft
        c_d_ave = (topRight + bottomRight) / 2.0
        d_minus_c = bottomRight - topRight

        if (isLE(x, bottomLeft)) 0.0

        else if (isLE(x, a_b_ave))
            2.0 * ((x - bottomLeft) / b_minus_a) ** 2

        else if (isLt(x, topLeft))
            1.0 - 2.0 * ((x - topLeft) / b_minus_a)** 2

        else if (isLE(x, topRight))
            1.0

        else if (isLE(x, c_d_ave))
            1 - 2 * ((x - topRight) / d_minus_c)**2

        else if (isLt(x, bottomRight))
            2 * ((x - bottomRight) / d_minus_c)** 2

        else 0.0
}

term.sigmoidDifference = function(x, left, rising, falling, right){
        a = 1.0 / (1 + exp(-rising * (x - left)))
        b = 1.0 / (1 + exp(-falling * (x - right)))
        abs(a - b)
}

term.sigmoidProduct = function(x, left, rising, falling, right){
        a = 1.0 / (1 + exp(-rising * (x - left)))
        b = 1.0 / (1 + exp(-falling * (x - right)))
        abs(a * b)
}

term.spike = function(x, center, width){
    exp(-abs( 10 / width * (x-center)))
}

#EDGES

term.binary = function(x, threshold, direction){
    if (isGE(direction,0.0) && isGE(x, threshold)){
        1.0
    }else if (isLt(direction, 0.0) && isLE(x, threshold)){
        1.0
    }else{
        0.0
    }
}

term.concave = function(x, inflection, end){
    if (isLE(inflection, end)){ #Concave increasing
        if (isLt(x, end)){
            (end - inflection) / (2 * end - inflection - x)
        }else{ 1.0 }
    } else{ #Concave decreasing
        if (isGt(x, end)){
            (inflection - end) / (inflection -2 * end + x)
        }else{ 1.0 }
    }
}


term.ramp = function(x, start, end){
        if (isEq(start, end)) 0.0
        
        else if (isLt(start, end)) {
            if (isLE(x, start)) 0.0
            else if (isGE(x, end))  1.0
            else (x - start) / (end - start)
        } else {
            if (isGE(x, start)) 0.0
            else if (isLE(x, end)) 1.0
            else (start - x) / ( start - end)
        }
}

term.sigmoid = function(x, inflection, slope){
    1.0 / (1.0 + exp(-slope * (x - inflection)))
}

term.sShape = function(x, start, end){
        average = (start + end) / 2
        difference = end - start

        if (isLE(x, start)) 0.0

        else if (isLE(x, average))
            2 * ((x - start) / difference) ** 2

        else if (isLt(x, end))
            1.0 - 2.0 * ((x - end) / difference) ** 2
        else 1.0
}

term.zShape = function(x, start, end){
        average = (start + end) / 2
        difference = end - start

        if (isLE(x, start)) 1.0

        else if (isLE(x, average))
            1.0 - 2.0 * ((x - start) / difference) ** 2

        else if (isLt(x, end))
            2.0 * ((x - end) / difference)** 2

        else 0.0
}







x = seq(0,1,length=500)
average = (max(x) + min(x))/2
diff = (max(x) - min(x))





dir.create('figure',showWarnings=F)


##################BASIC

triangle.df = data.frame(x, y=sapply(x, term.triangle, min(x), average, max(x)))
image = ggplot(triangle.df, aes(x,y, size=2, lineend='round')) + geom_line() + ylab(expression(mu(x))) + theme(legend.position='none')
ggsave('figure/triangle.svg', image, width=3, height=3)


trapezoid.df = data.frame(x, y=sapply(x, term.trapezoid, min(x), min(x) + .25 * diff, min(x) + .75*diff, max(x)))
image = ggplot(trapezoid.df, aes(x,y, size=2, lineend='round')) + geom_line() + ylab(expression(mu(x))) + theme(legend.position='none')
ggsave('figure/trapezoid.svg', image, width=3, height=3)


rectangle.df = data.frame(x, y=sapply(x, term.rectangle, min(x) + .25*diff,  min(x) + .75*diff))
image = ggplot(rectangle.df, aes(x,y, size=2, lineend='round')) + geom_line() + ylab(expression(mu(x))) + theme(legend.position='none')
ggsave('figure/rectangle.svg', image, width=3, height=3)


discrete.x = x[c(1, seq(10, 495, 10), 500)]
discrete.df = data.frame(x=discrete.x, y=sapply(discrete.x, term.discrete, min(x),  max(x)))
image = ggplot(discrete.df, aes(x,y, size=2, lineend='round')) + geom_point() + ylab(expression(mu(x))) + theme(legend.position='none')
ggsave('figure/discrete.svg', image, width=3, height=3)



#################EXTENDED

cosine.df = data.frame(x, y=sapply(x, term.cosine, average, diff))
image = ggplot(cosine.df, aes(x,y, size=2, lineend='round')) + geom_line() + ylab(expression(mu(x))) + theme(legend.position='none')
ggsave('figure/cosine.svg', image, width=3, height=3)


gaussian.df = data.frame(x, y=sapply(x, term.gaussian, average,  .2*diff))
image = ggplot(gaussian.df, aes(x,y, size=2, lineend='round')) + geom_line() + ylab(expression(mu(x))) + theme(legend.position='none')
ggsave('figure/gaussian.svg', image, width=3, height=3)


gaussianProduct.df = data.frame(x, y=sapply(x, term.gaussianProduct, average+.1,  .2*diff, average-.1, .2*diff))
image = ggplot(gaussianProduct.df, aes(x,y, size=2, lineend='round')) + geom_line() + ylab(expression(mu(x))) + theme(legend.position='none')
ggsave('figure/gaussianProduct.svg', image, width=3, height=3)


bell.df = data.frame(x, y=sapply(x, term.bell, average,  .25*diff, 3.0))
image = ggplot(bell.df, aes(x,y, size=2, lineend='round')) + geom_line() + ylab(expression(mu(x))) + theme(legend.position='none')
ggsave('figure/bell.svg', image, width=3, height=3)


piShape.df = data.frame(x, y=sapply(x, term.piShape, min(x), average, average, max(x)))
image = ggplot(piShape.df, aes(x,y, size=2, lineend='round')) + geom_line() + ylab(expression(mu(x))) + theme(legend.position='none')
ggsave('figure/piShape.svg', image, width=3, height=3)


sigmoidDifference.df = data.frame(x, y=sapply(x, term.sigmoidDifference, min(x) + .25*diff, 20/diff, 20/diff, min(x)+.75*diff))
image = ggplot(sigmoidDifference.df, aes(x,y, size=2, lineend='round')) + geom_line() + ylab(expression(mu(x))) + theme(legend.position='none')
ggsave('figure/sigmoidDifference.svg', image, width=3, height=3)


sigmoidProduct.df = data.frame(x, y=sapply(x, term.sigmoidProduct, min(x) + .25*diff, 10/diff, -10/diff, min(x)+.75*diff))
image = ggplot(sigmoidProduct.df, aes(x,y, size=2, lineend='round')) + geom_line() + ylab(expression(mu(x))) + theme(legend.position='none')
ggsave('figure/sigmoidProduct.svg', image, width=3, height=3)


spike.df = data.frame(x, y=sapply(x, term.spike, average, diff))
image = ggplot(spike.df, aes(x,y, size=2, lineend='round')) + geom_line() + ylab(expression(mu(x))) + theme(legend.position='none')
ggsave('figure/spike.svg', image, width=3, height=3)



###############EDGE

#Binary
binary.dfa = data.frame(x, y=sapply(x, term.binary, min(x) + .25*diff, -1))
binary.dfb = data.frame(x, y=sapply(x, term.binary, min(x) + .75*diff, 1))
image = ggplot(binary.dfa, aes(x,y, size=2, lineend='round')) + 
        geom_line(data=binary.dfb, aes(x,y, size=2, lineend='round')) + 
        geom_line() + ylab(expression(mu(x))) + theme(legend.position='none')   
ggsave('figure/binary.svg', image, width=3, height=3)

#Concave
concave.dfa = data.frame(x, y=sapply(x, term.concave, average, max(x)-.2))
concave.dfb = data.frame(x, y=sapply(x, term.concave, average, 1-(max(x)-.2)))
image = ggplot(concave.dfa, aes(x,y, size=2, lineend='round')) + 
        geom_line(data=concave.dfb, aes(x,y, size=2, lineend='round')) + 
        geom_line() + ylab(expression(mu(x))) + theme(legend.position='none')   
ggsave('figure/concave.svg', image, width=3, height=3)

#RAMP
ramp.dfa = data.frame(x, y=sapply(x, term.ramp, max(x)-.2, min(x)+.2))
ramp.dfb = data.frame(x, y=sapply(x, term.ramp, min(x)+.2, max(x)-.2))
image = ggplot(ramp.dfa, aes(x,y, size=2, lineend='round')) + 
        geom_line(data=ramp.dfb, aes(x,y, size=2, lineend='round')) + 
        geom_line() + ylab(expression(mu(x))) + theme(legend.position='none') 
ggsave('figure/ramp.svg', image, width=3, height=3)


sigmoid.dfa = data.frame(x, y=sapply(x, term.sigmoid, average, 20/diff))
sigmoid.dfb = data.frame(x, y=sapply(x, term.sigmoid, average, -20/diff))
image = ggplot(sigmoid.dfa, aes(x,y, size=2, lineend='round')) + 
        geom_line(data=sigmoid.dfb, aes(x,y, size=2, lineend='round')) + 
        geom_line() + ylab(expression(mu(x))) + theme(legend.position='none')
ggsave('figure/sigmoid.svg', image, width=3, height=3)


sShape.df = data.frame(x, y=sapply(x, term.sShape, min(x), max(x)))
image = ggplot(sShape.df, aes(x,y, size=2, lineend='round')) + geom_line() + ylab(expression(mu(x))) + theme(legend.position='none')
ggsave('figure/sShape.svg', image, width=3, height=3)


zShape.df = data.frame(x, y=sapply(x, term.zShape, min(x), max(x)))
image = ggplot(zShape.df, aes(x,y, size=2, lineend='round')) + geom_line() + ylab(expression(mu(x))) + theme(legend.position='none')
ggsave('figure/zShape.svg', image, width=3, height=3)



