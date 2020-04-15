open NotificationContext;

let use = () => React.useContext(context);

module Provider = {
  [@react.component]
  let make = (~children, ~value) => {
    <NotificationContext value> children </NotificationContext>;
  };
};