package cmd

import (
	"context"
	"fmt"
	"log"
	"net"

	"google.golang.org/grpc"

	pb "github.com/poseidonos/pos-exporter/api/pos.metric"
)

const (
	host           = "localhost"
	subscriberPort = "50051"
)

type metricManagerServer struct {
	pb.MetricManagerServer
}

func (s *metricManagerServer) MetricPublish(ctx context.Context, in *pb.MetricPublishRequest) (*pb.MetricPublishResponse, error) {
	err := parseRequest(in)
	if err != nil {
		log.Fatalf("failed to Parse Metric")
	}

	var ret pb.MetricPublishResponse
	ret.TotalReceivedMetrics = uint64(len(in.GetMetrics()))
	return &ret, err
}

func newServer() *metricManagerServer {
	s := &metricManagerServer{}
	return s
}

func runSubscriber() {
	lis, err := net.Listen("tcp", fmt.Sprintf("%s:%s", host, subscriberPort))
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}

	var opts []grpc.ServerOption
	grpcServer := grpc.NewServer(opts...)
	pb.RegisterMetricManagerServer(grpcServer, newServer())
	grpcServer.Serve(lis)
}

func parseRequest(in *pb.MetricPublishRequest) error {
	for _, metric := range in.GetMetrics() {
		fmt.Println(metric)
		name := metric.GetName()
		labelMap := makeLabelMap(metric.GetLabels())
		switch metric.GetType() {
		case pb.MetricTypes_COUNTER:
			value := metric.GetCounterValue()
			parsed := CounterMetric{name, labelMap, value}
			addCounter(&parsed)
		case pb.MetricTypes_GAUGE:
			value := metric.GetGaugeValue()
			parsed := GaugeMetric{name, labelMap, value}
			addGauge(&parsed)
		}
	}
	return nil
}

func makeLabelMap(labels []*pb.Label) *map[string]string {
	var labelMap map[string]string = map[string]string{}
	for _, label := range labels {
		labelMap[label.GetKey()] = label.GetValue()
	}

	return &labelMap
}
