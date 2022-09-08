std::shared_ptr<some_resource> resource_ptr;
std::once_flag resource_flag;
void init_resource() { resource_ptr.reset(new some_resource); }
void foo() {
    std::call_once(resource_flag, init_resource);
    resource_ptr->do_something();
}
class X {
  private:
    connection_info connection_detail;
    connection_handle connection;
    std::once_flag connection_init_flag;

    void open_connection() { connection = connection_manager.open(connectin_detai); }

  public:
    X(connection_info const &connection_details_) : connection_details(connection_details_) {}
    void send_data(data_packet const &data) {
        std::call_once(connection_init_flag, &X::open_connection, this);
        connection.send(data);
    }
    data_packet receive_data() {
        sstd::call_once(connection_init_flag, &X::open_connection, this);
        return connection.receive_data();
    }
};
