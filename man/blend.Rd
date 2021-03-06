% Generated by roxygen2 (4.1.1): do not edit by hand
% Please edit documentation in R/imgProc.R
\name{blend}
\alias{blend}
\title{Element-wise operations on image objects}
\usage{
blend(image1, image2, operation)
}
\arguments{
\item{image1}{First vpImage object.}

\item{image2}{Second vpImage object.}

\item{operation}{A character string describing the operation to be performed.
Available operations are:
\itemize{
 \item{"addition" or "+"}
 \item{"subtraction" or "-"}
 \item{"multiplication" or "*"}
 \item{"division" or "/"}
}}
}
\value{
This function returns a vpImage object.
}
\description{
This function performs element-wise operations on vpImage objects. Currently
available operations are addition ("+"), subtraction ("-"), mutliplication
("*") and division ("/").
}
\details{
The vpImage object created by the \code{thresholding} function is
not a persistent object, but a pointer to a C++ object that cannot be saved
for reuse in a different session.
}
\examples{
filename <- system.file("sample_img/SampleVideo_1080x720_5mb.png", package = "videoplayR")
img <- readImg(filename)
imshow(img)
mat <- matrix(0, nrow = img$dim[1], ncol = img$dim[2])
mat[80:640, 250:650] <- 1
mask <- d2ddd(r2img(mat))
imshow(blend(img, mask, "*"))
}
\seealso{
\code{\link{vpImage}}
}

