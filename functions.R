#' Read VTune data from my summary file
#'
#' In the resulting tibble, the column 'type' indicates what kind of measurement
#' is carried in the 't' column for that row.
#'     full: t is the time in seconds taken by this function in the full program
#'
#' @param filename
#'
#' @return a tibble
#' @export
#'
read_vtune <- function(filename)
{
  d <- read_csv(filename, col_types="ifdf")
  pivot_wider(d, names_from=func, values_from=t)
}

#' Read VTune hotspot reports
#'
#' @param filename
#'
#' @return a hotspot tibble
#' @export
#'
#' @examples
read_vtune_hotspots <- function(filename)
{
  checkmate::assert_file(filename)
  readr::read_tsv(filename, show_col_types=FALSE) |>
    rename(func = Function,
           t = `CPU Time`,
           teff = `CPU Time:Effective Time`,
           tspin = `CPU Time:Spin Time`,
           tspinimb = `CPU Time:Spin Time:Imbalance or Serial Spinning`,
           tspinlock = `CPU Time:Spin Time:Lock Contention`,
           tspinother = `CPU Time:Spin Time:Other`,
           tover = `CPU Time:Overhead Time`,
           tovercreate = `CPU Time:Overhead Time:Creation`,
           toversched = `CPU Time:Overhead Time:Scheduling`,
           toverred = `CPU Time:Overhead Time:Reduction`,
           toveratom = `CPU Time:Overhead Time:Atomics`,
           toverother = `CPU Time:Overhead Time:Other`,
           lib = Module,
           funcname = `Function (Full)`,
           file = `Source File`,
           addr = `Start Address`)
}

read_channel_data <- function(filename)
{
  x <- readr::read_tsv(filename, col_types = "iiiii")
  x
}

read_measurement_data <- function(filename)
{
  x <- readr::read_tsv(filename, col_types = "iiiiii")
  x
}

make_analysis_dataframes <- function(orig_channels, orig_meas)
{
  # Generate unique event ids "eid".
  # For some datasets this is trivial (we could have used just `event`), but that
  # is not true for all data sets. This is more robust.
  event_ids <-
    orig_channels |>
    select(run, subrun, event) |>
    unique() |>
    mutate(eid = row_number())

  # Add the eid into the per-channel data frame, and remove the now redundant
  # columns run, subrun, event. Do the same for the per-measurement data frame.
  channels <-
    left_join(orig_channels, event_ids) |>
    select(eid, channel, nmeas) |>
    mutate(eid = factor(eid), channel=factor(channel), nmeas = nmeas)
  meas <-
    left_join(orig_meas, event_ids) |>
    select(eid, channel, time, nphot) |>
    mutate(eid = factor(eid), channel=factor(channel), time = time, nphot = nphot)

  # Get the number of photons summed across all measurements in for each channel in each event.
  tmp <-
    group_by(meas, eid, channel) |>
    summarize(nphots = sum(nphot), .groups="drop")

  channels <- inner_join(channels, tmp)
  list(channels = channels, meas = meas)
}

read_dataframes <- function()
{
    run_names <- c("acosd", "acos4", "acos5", "orig") 
    channels_files <- list.files(path = "physics_validation_data",
                                 pattern = glob2rx("channels*.tsv"),
                                 full.names = TRUE)
    measurements_files <- list.files(path = "physics_validation_data",
                                     pattern = glob2rx("measurements*.tsv.xz"),
                                     full.names = TRUE)
    channels <- lapply(channels_files, read_channel_data)
    measurements <- lapply(measurements_files, read_measurement_data)
    names(channels) <- run_names
    names(measurements) <- run_names
    channels <- bind_rows(channels, .id = "alg")
    channels$alg <-factor(channels$alg,
                          levels = c("acosd", "orig", "acos4", "acos5"),
                          ordered = TRUE)
    measurements <- bind_rows(measurements, .id = "alg")
    chs <- pivot_wider(channels,
                       id_cols = c(run, subrun, event, channel),
                       names_from = alg,
                       values_from = nmeas)
    chs <- mutate(chs,
                  d4 = acos4 - acosd,
                  d5 = acos5 - acosd,
                  do = orig - acosd) 
    list(channels=channels, measurements=measurements, chs=chs)
}

#' Adjust the raw dataframe read from nanobench to a helpful format
#' 
#' This function breaks up the `name` column in the input `d` to
#' create several comments.
#'
#' @param d the dataframe, as read by read.so::read_md
#'
#' @return a tibble
#' @export
#'
adjust_raw_df <- function(d) {
  #mutate(d, spc = str_remove_all(`simphotons choices`, "`"), .keep="unused") |>
  d |>
    separate_wider_delim(cols=.data$name,
                         delim="_",
                         names=c("fcn", "structure", "size")) |>
    mutate(structure=as_factor(structure),
           fcn=as_factor(fcn),
           size=as.integer(size))}